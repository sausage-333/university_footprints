// Jang Kangwook 20150651

#define _GNU_SOURCE
#include "dynarray.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define pipe_token "operator_|"
#define in_token "operator_<"
#define out_token "operator_>"

enum CharState {
	CHARACTER = 1,
	QUOTE = 2, 
	PIPE = 3, 
	WHITE_SPACE = 4
};


enum RedirectionToken {
	OUT_TOKEN = 0, 
	IN_TOKEN = 1, 
	PIPE_TOKEN = 2, 
	NOTHING = 3
};


// 시스템 이름과 함께 프린트를 해준다.
void fprintf_error_message_with_program_name(char program_name[], char error_message[]){
	fprintf(stderr, "%s: %s\n", program_name, error_message);
}


//나중에 free할 시, malloc이 아닌 토큰들로 에러가 뜨는것을 방지하기 위해, operator들은 따로 malloc을 해준다.
void make_operator_token(char program_name[], DynArray_T token_array, char *token_name) {
	assert(token_array != NULL);
	assert(token_name[0] != '\0');
	char* token = (char *) malloc (sizeof(char)*1024);
	strcat(token, token_name);
	if (DynArray_add(token_array, token) == 0) {
		fprintf_error_message_with_program_name(program_name, strerror(errno));
		assert(0);
	}
}


// 토큰을 생성
void make_token(char program_name[], DynArray_T token_array, char *token_name) {
	assert(token_array != NULL);
	assert(token_name[0] != '\0');
	if (DynArray_add(token_array, token_name) == 0) {
		fprintf_error_message_with_program_name(program_name, strerror(errno));
		assert(0);
	}
}


// syntax를 확인하는 단계
// 총 4개의 state를 두고 문자를 받을때마다 state를 변경한다.
// | 와 >, < 은 specitial한 문자로 따로 string으로 넘겨줘 make operator token에서 말록으로 생성
int lex_line(char program_name[], char command_line[], DynArray_T token_array) {
	assert(token_array != NULL);
	enum CharState char_state = WHITE_SPACE;
	char* token = (char *) malloc (sizeof(char)*1024);
	char line_character[2];
	int position = 0;
	line_character[1] = '\0';
	while ((line_character[0] = command_line[position++]) != '\0') {
		switch (char_state) {
			case CHARACTER:
				switch (line_character[0]) {
					case '|':
						char_state = PIPE;
						make_token(program_name, token_array, token);
						break;
					case '"':
						char_state = QUOTE;
						break;
					default:
						if (isspace(line_character[0])) {
							make_token(program_name, token_array, token);
							char_state = WHITE_SPACE;
						}
						else {
							strcat(token, line_character);
						}
						break;
				}
				break;
			case QUOTE:
				switch (line_character[0]) {
					case '"':
						char_state = CHARACTER;
						break;
					default:
						strcat(token, line_character);
						break;
				}
				break;
			case PIPE:
				make_operator_token(program_name, token_array, pipe_token);
				switch (line_character[0]) {
					case '"':
						token = (char *) malloc (sizeof(char)*1024);
						char_state = QUOTE;
						break;
					case '|':
						break;
					default:
						if (isspace(line_character[0])){
							char_state = WHITE_SPACE;
						} 
						else {
							char_state = CHARACTER;
							token = (char *) malloc (sizeof(char)*1024);
							strcat(token, line_character);
						}
						break;
				}
				break;
			case WHITE_SPACE:
				if(!isspace(line_character[0])) {
					switch (line_character[0]) {
						case '|':
							char_state = PIPE;
							break;
						case '>':
							if (isspace(command_line[position]) || command_line[position] == '\0') {
								make_operator_token(program_name, token_array, out_token);
							}
							else {
								token = (char *) malloc (sizeof(char)*1024);
								strcat(token, line_character);
								char_state = CHARACTER;
							}
							break;
						case '<':
							if (isspace(command_line[position]) || command_line[position] == '\0') {
								make_operator_token(program_name, token_array, in_token);
							}
							else {
								token = (char *) malloc (sizeof(char)*1024);
								strcat(token, line_character);
								char_state = CHARACTER;
							}
							break;
						case '"':
							token = (char *) malloc (sizeof(char)*1024);
							char_state = QUOTE;
							break;
						default:
							token = (char *) malloc (sizeof(char)*1024);
							strcat(token, line_character);
							char_state = CHARACTER;
							break;
					}
				}
				break;
			default:
				break;
		}
	}
	switch (char_state) {
		case CHARACTER:
			make_token(program_name, token_array, token);
			return 1;
		case QUOTE:		//" 가 짝이 없이 끝났음을 의미
			fprintf_error_message_with_program_name(program_name, "ERROR - unmatched quote");
			return 0;
		case PIPE:
			make_operator_token(program_name, token_array, pipe_token);
			return 1;
		case WHITE_SPACE:
			return 1;
	}
	return 1;
}


// 토큰들에 대해 좀 더 정밀하게 조사, Parsing하는 단계를 의미한다.
// setenv, unsetenv, cd, exit처럼 특정한 함수 4개륾 먼저 체크한 후, 아닐시 제너럴하게 해결
// 항상 마지막에 special token이 오면 error
int parse_tokens(char program_name[], DynArray_T token_array) {
	assert(token_array != NULL);
	int token_length = 0;
	char *token;
	int token_index = 0;

	if((token_length = DynArray_getLength(token_array)) == 0) {
		return 1;
	} 
	token = DynArray_get(token_array, token_index);

	if (strcmp(token, "setenv") == 0) {
		if (token_length == 1) {
			fprintf_error_message_with_program_name(program_name, "no setenv command arguments found");
			return 0;
		}
		else if (token_length > 3) {
			fprintf_error_message_with_program_name(program_name, "max number argument of setenv command are two");
			return 0;
		}
	}
	else if(strcmp(token, "unsetenv") == 0) {
		if (token_length == 1) {
			fprintf_error_message_with_program_name(program_name, "no unsetenv command argument found");
			return 0;
		}
		else if (token_length >= 3) {
			fprintf_error_message_with_program_name(program_name, "max number argument of unsetenv command are one");
			return 0;
		}
	}
	else if(strcmp(token, "cd") == 0 && token_length > 2) {
		fprintf_error_message_with_program_name(program_name, "max number argument of cd command are one");
			return 0;
	}
	else if(strcmp(token, "exit") == 0 && token_length != 1) {
		fprintf_error_message_with_program_name(program_name, "exit command can't have arguments");
			return 0;
	}
	else {
		if (strcmp(token, pipe_token) == 0 || strcmp(token, out_token) == 0 || strcmp(token, in_token) == 0) {
			fprintf_error_message_with_program_name(program_name, "Invalid: Missing command name");
			return 0;
		} 
		else {
			char *prev_token = DynArray_get(token_array, 0);
			enum RedirectionToken redirection_token_status = NOTHING;

			// 과거의 redirection 이나 pipe 토큰의 기록을 가지고 있는다.
			// 이를 통해 연속으로 했을 시 error를 나타낸다.
			// 또한 state를 만드는데, 이것은 가장 최근에 인식했던 specitial한 토큰을 의미한다.
			// 이를 통해 중복을 체크할 수 있다.
			while(token_length > token_index) {
				token = DynArray_get(token_array, token_index++);
				switch (redirection_token_status) {
					case OUT_TOKEN:			// error의 경우는  > >, > |, > <, > token >, > token |
						if (strcmp(token, pipe_token) == 0) {
							if (strcmp(prev_token, out_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Standard output redirection without file name");
							}
							else {
								fprintf_error_message_with_program_name(program_name, "Invalid: Multiple redirection of standard output");
							}	
							return 0;
						}
						else if (strcmp(token, out_token) == 0) {
							if (strcmp(prev_token, out_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Standard output redirection without file name");
							}
							else {
								fprintf_error_message_with_program_name(program_name, "Invalid: Multiple redirection of standard output");
							}	
							return 0;
						}
						else if (strcmp(token, in_token) == 0) {
							if (strcmp(prev_token, out_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Standard output redirection without file name");
								return 0;
							}
							redirection_token_status = IN_TOKEN;
							prev_token = token;
						}
						else {
							prev_token = token;
						}
						break;
					case IN_TOKEN:		// error의 경우는  < <, < |, < >, < token <
						if (strcmp(token, pipe_token) == 0) {
							if (strcmp(prev_token, in_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Standard input redirection without file name");
								return 0;
							}
							redirection_token_status = PIPE_TOKEN;
							prev_token = token;
						}
						else if (strcmp(token, out_token) == 0) {
							if (strcmp(prev_token, in_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Standard input redirection without file name");
								return 0;
							}
							redirection_token_status = OUT_TOKEN;
							prev_token = token;
						}
						else if (strcmp(token, in_token) == 0) {
							if (strcmp(prev_token, in_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Standard input redirection without file name");
							} else {
								fprintf_error_message_with_program_name(program_name, "Invalid: Multiple redirection of standard input");
							}
							return 0;
						}
						else {
							prev_token = token;
						}
						break;
					case PIPE_TOKEN:		// error의 경우는  | |, | <, | >, | token <
						if (strcmp(token, pipe_token) == 0) {
							if (strcmp(prev_token, pipe_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Pipe destination not specified");
								return 0;
							} 
							prev_token = token;
						}
						else if (strcmp(token, out_token) == 0) {
							if (strcmp(prev_token, pipe_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Pipe destination not specified");
								return 0;
							}
							redirection_token_status = OUT_TOKEN;
							prev_token = token;
						}
						else if (strcmp(token, in_token) == 0) {
							if (strcmp(prev_token, pipe_token) == 0) {
								fprintf_error_message_with_program_name(program_name, "Invalid: Pipe destination not specified");
							}
							else {
								fprintf_error_message_with_program_name(program_name, "Invalid: Multiple redirection of standard input");
							}	
							return 0;
						}
						else {
							prev_token = token;
						}
						break;
					case NOTHING:
						if (strcmp(token, pipe_token) == 0) {
							redirection_token_status = PIPE_TOKEN;
							prev_token = token;
						}
						else if (strcmp(token, out_token) == 0) {
							redirection_token_status = OUT_TOKEN;
							prev_token = token;
						}
						else if (strcmp(token, in_token) == 0) {
							redirection_token_status = IN_TOKEN;
							prev_token = token;
						}
						else {
							prev_token = token;
						}
						break;
				}
			}
			// 마지막의 경우
			if (strcmp(prev_token, pipe_token) == 0) {		// 마지막이 | 일시
				fprintf_error_message_with_program_name(program_name, "Invalid: Missing command name");
				return 0;
			} 
			else if (strcmp(prev_token, out_token) == 0) {		// 마지막이 > 일시
				fprintf_error_message_with_program_name(program_name, "Invalid: Standard output redirection without file name");
				return 0;
			} 
			else if (strcmp(prev_token, in_token) == 0) {		// 마지막이 < 일시
				fprintf_error_message_with_program_name(program_name, "Invalid: Standard input redirection without file name");
				return 0;
			}
		}
	}
	return 1;

}

// command_line에 대해 redirection token이 있나 확인한다.
// 먼저 line을 뽑고하기에 , redirection을 찾고 이의 index를 리턴
// 없을 시, -1을 리턴한다.
int get_redirection_token_index(char* command_line[], int command_length) {
	int i;
	for (i = 0; i < command_length; i++) {
		if (strcmp(command_line[i], out_token) == 0 || strcmp(command_line[i], in_token) == 0) {
			return i;
		}
	}
	return -1;
}


// redirection을 처리한다.
// 여기서 > 이 들어온다면 output을 파일 생성으로
// < 이 온다면 input을 파일 변수로 받게 하고, 생성했던 fd를 지워준다.
// 그 후, redirection token을 지워버린다. 2개의 토큰 (redirection, target??) 이 사라졌으므로 2칸씩 땡긴다.
void redirection_command_line(
	char program_name[], 
	char* command_line[],
	int command_length, 
	int redirection_token_index
) {
	
	if (strcmp(command_line[redirection_token_index], out_token) == 0){
		int fd = creat(command_line[redirection_token_index+1], 0600);
		dup2(fd,STDOUT_FILENO);
		close(fd);
	}
	else if (strcmp(command_line[redirection_token_index], in_token) == 0){
		int fd = open(command_line[redirection_token_index+1], O_RDONLY);
		if(fd == -1){
			fprintf_error_message_with_program_name(program_name, strerror(errno));
		}
		dup2(fd,STDIN_FILENO);
		close(fd);
	}
	for (; redirection_token_index + 2 <= command_length; redirection_token_index++){
		command_line[redirection_token_index] = command_line[redirection_token_index+2];
	}
	command_line[redirection_token_index] = 0;
}


//싱행하는 단계로써 parse와 마찬가지로 setenc, unsetenv, cd, exit를 먼저 처리한다.
// 이는 개수가 정해져있기 때문이다.
void execute_parsed_tokens(char program_name[], DynArray_T token_array) {
	assert(token_array != NULL);
	int token_length;
	char *token, *first_argument, *second_argument;
	if((token_length = DynArray_getLength(token_array)) == 0) {
		return ;
	}
	token = DynArray_get(token_array, 0);

	if (strcmp(token, "setenv") == 0) {
		first_argument = DynArray_get(token_array, 1);
		if (token_length == 3) {
			second_argument = DynArray_get(token_array, 2);
		} 
		else {
			second_argument = "";
		}
		setenv(first_argument, second_argument, 1);
	}
	else if(strcmp(token, "unsetenv") == 0) {
		first_argument = DynArray_get(token_array, 1);
		unsetenv(DynArray_get(token_array, 1));
	}
	else if(strcmp(token, "cd") == 0) {
		if (token_length == 2) {
			first_argument = DynArray_get(token_array, 1);
		}
		else {
			if((first_argument = getenv("HOME")) == NULL) {		// Home으로 보내는 코드
				first_argument = "./";
			}
		}
		if (chdir(first_argument) == -1) {
			fprintf_error_message_with_program_name(program_name, strerror(errno));
		}
	}
	else if(strcmp(token, "exit") == 0) {
		exit(EXIT_SUCCESS);
	}
	//하나하나 읽어가는 부분.
	// 먼저 pipe를 만날때까지 command_line에 넣고, 이를 만날 시, pipe함수를 호출하며 dup를 통해 fd를 관리
	// pipe의 개수에 따라 달라지므로 fds1, fds2 즉 2개를 만들어 준다.
	// eecvp를 통해 하는 실행은 항상 fork를 통해 child에서 실행
	// child에서는 sigint를 sig dfl 로 걸어 놓아 언제는 sigint가 호출할 수 있도록 한다.
	else {
		int status;
		char* command_line[10];
		int fds1[2], fds2[2];
		pid_t pid;
		int token_index = 0;
		int pipe_num = 0;
		int command_length = 0;	 
		int is_in_redirection_token = 0;
		int is_out_redirection_token = 0;
		for (int i = 0; i < 10; i++) {   //커맨드를 기억할 곳
			command_line[i] = 0;
		}
		while(token_index < token_length) {
			token = DynArray_get(token_array, token_index++);
			if (strcmp(token, pipe_token) == 0) {
				int redirection_token_index;
				// redirection을 while로 계속 찾는다 (2개일 수 있으므로)
				while((redirection_token_index = get_redirection_token_index(command_line, command_length)) != -1) {
					// fail이 나거나 완료되었을 시, 변경된 fd 1과 0을 다시 되살린다.
					if (strcmp(command_line[redirection_token_index], out_token) == 0){
						is_out_redirection_token = 1;
					} 
					if (strcmp(command_line[redirection_token_index], in_token) == 0){
						is_in_redirection_token = 1;
					}
					redirection_command_line(program_name, command_line, command_length, redirection_token_index);
					command_length = command_length - 2; // 한 번 실행 시, 2개의 토큰이 사라졌으므로
				}
				fflush(NULL);
				pipe_num++;
				// pipe를 만날 시 1개를 추가해주며, 그때마다 pipe함수를 불러준다.
				if (pipe_num == 1 && (pipe(fds1)) == -1) {
					fprintf_error_message_with_program_name(program_name, strerror(errno));
					exit(-1);
				}
				else if (pipe_num == 2 && (pipe(fds2)) == -1) {
					fprintf_error_message_with_program_name(program_name, strerror(errno));
					exit(-1);
				}
				if ((pid = fork()) == 0) {
					signal(SIGINT, SIG_DFL);	//child는 sigint를 실행하도록
					// 아래는 1일시, 2일시의 pipe처리를 해준다. 쉽게 내 인풋을 넘기고, 아우풋을 받는 그런 파이프 모형을 생각.
					// 마지막 1개의 command에서 처리할 것을 생각하면 여기에선 이정도가 끝이다.
					// pipe가 1개일 시 pipe를 기준으로 왼쪽
					if (pipe_num==1) {
						dup2(fds1[1], 1);
						close(fds1[0]);
						close(fds1[1]);
					} 
					// pipe가 2개일 시, 가운데 처리, (맨 왼쪽 처리는 pipe_num == 1에서 처리된다)
					else if (pipe_num == 2) {
						dup2(fds1[0], 0);
						close(fds1[1]);
						close(fds1[0]);
						dup2(fds2[1], 1);
						close(fds2[0]);
						close(fds2[1]);
					}
					execvp(command_line[0], command_line);
					fprintf_error_message_with_program_name(program_name, strerror(errno));
					// 실패했을 시에도, redirection을 복구시켜주어야한다.
					if (is_out_redirection_token == 1){
						dup2(STDERR_FILENO, STDOUT_FILENO); 
					}
					if (is_in_redirection_token == 1){
						dup2(STDERR_FILENO, STDIN_FILENO);
					}
					exit(EXIT_FAILURE);
				}
				if (is_out_redirection_token == 1){
					dup2(STDERR_FILENO, STDOUT_FILENO); 
				}
				if (is_in_redirection_token == 1){
					dup2(STDERR_FILENO, STDIN_FILENO);
				}
				if (pipe_num==2) {
					close(fds1[0]);
					close(fds1[1]);
				}
				waitpid(pid, &status, 0);
				for (; command_length != 0; command_length--) {
					command_line[command_length - 1] = 0;
				}
			} 
			else {	//아무 특정한 것이 아닐 시 커맨드에 추가
				command_line[command_length++] = token;
			}
			// 마지막 command 실행 라
			if (token_index == token_length) {
				int redirection_token_index;
				while((redirection_token_index = get_redirection_token_index(command_line, command_length)) != -1) {
					// fail이 나거나 완료되었을 시, 변경된 fd 1과 0을 다시 되살린다.
					if (strcmp(command_line[redirection_token_index], out_token) == 0){
						is_out_redirection_token = 1;
					} 
					if (strcmp(command_line[redirection_token_index], in_token) == 0){
						is_in_redirection_token = 1;
					}
					redirection_command_line(program_name, command_line, command_length, redirection_token_index);
					command_length = command_length - 2; 
				}

				if ((pid = fork()) == 0) {
					signal(SIGINT, SIG_DFL);
					if (pipe_num==1) {
						dup2(fds1[0], 0);
						close(fds1[0]);
						close(fds1[1]);
					} 
					else if (pipe_num == 2) {
						//close(fds2[1]);
						dup2(fds2[0], 0);
						close(fds2[0]);
						close(fds2[1]);
					}
					execvp(command_line[0], command_line);

					fprintf_error_message_with_program_name(program_name, strerror(errno));
					if (is_out_redirection_token == 1){
						dup2(STDERR_FILENO, STDOUT_FILENO); 
					}
					if (is_in_redirection_token == 1){
						dup2(STDERR_FILENO, STDIN_FILENO);
					}
					exit(EXIT_FAILURE);
				}
				if (is_out_redirection_token == 1){
					dup2(STDERR_FILENO, STDOUT_FILENO); 
				}
				if (is_in_redirection_token == 1){
					dup2(STDERR_FILENO, STDIN_FILENO);
				}
				if (pipe_num==1) {
					close(fds1[0]);
					close(fds1[1]);
				}
				if (pipe_num==2) {
					close(fds2[0]);
					close(fds2[1]);
				}
				waitpid(pid, &status, 0);
			}
		}
	}
}

