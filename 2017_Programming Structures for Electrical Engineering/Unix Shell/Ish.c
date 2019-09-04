// Jang Kangwook 20150651

#include <assert.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include "IshToken.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "dynarray.h"
#include <unistd.h>


static int sigquit_exit_flag = 0; //quit시그널을 받으면 1, alarm을 받으면 0을 통해 5초를 컨트
static char* program_name;

void free_token(void *pvElement, void *pvExtra) {
        if (pvElement != NULL) {
                free(pvElement);
        }
}
void free_token_array(DynArray_T token_array) {
        if (DynArray_getLength(token_array) > 0) {
                DynArray_map(token_array, free_token, NULL);
        }

        DynArray_free(token_array);
}

static void sigquit_handler(int sig){
        if (sigquit_exit_flag){ //5초 이내에 1번 더 불렸다면, alarm이 완료가 되지 못했기에 상태가 1일것.
                exit(EXIT_SUCCESS);
        }
        fprintf(stdout, "\nType Ctrl-\\ again within 5 seconds to exit.\n");
        sigquit_exit_flag = !sigquit_exit_flag;
        alarm(5);
}


static void sigalarm_handler(int sig){
        sigquit_exit_flag = !sigquit_exit_flag; //5초의 alarm이 지나면 다시 quit을 2번 눌러야 나가게끔 할 수 있도록.
}


void execution(char program_name[], char* command_line, FILE *fp, int is_file_read) {
        DynArray_T token_array = DynArray_new(0);       // Token들을 담을 Dynamic Array를 생성

        if (is_file_read){              //File read에서는 %% %s를 해준다. 하지만 아닐 시, 미리 %을 하면서 프린트 할 필요가 없다.
                fprintf(stdout, "%% %s", command_line); // command_line 마지막에  \n이 있기에 따로 \n을 넣어주지 않>아도 된다.
        }

        if (lex_line(program_name, command_line, token_array)){
                if (parse_tokens(program_name, token_array)) {
                        execute_parsed_tokens(program_name, token_array);
                }
        //      else {
        //              fprintf(stderr, "%s: Invalid Parsing\n", program_name);
        //      }
        }
        else {
                fprintf(stderr, "%s: Invalid line\n", program_name);
        }

        free_token_array(token_array);
}


int main(int argc, char* argv[]) {
        sigset_t set;
        FILE *fp;
        char *command_line = (char *) malloc (sizeof(char)*1024);

        sigemptyset(&set);      //Signal Set들을 다 지워버린 후, 필요한 Signal만 넣어주고 procmask를 통해 unblock을 보장해준다.
        sigaddset(&set, SIGINT);
        signal(SIGINT, SIG_IGN);
        sigaddset(&set, SIGALRM);
        signal(SIGALRM, sigalarm_handler);
        sigaddset(&set, SIGQUIT);
        signal(SIGQUIT, sigquit_handler);
        sigprocmask(SIG_UNBLOCK, &set, NULL);


        program_name = argv[0];

        if(chdir(getenv("HOME")) == -1) {       //HOME을 통해 디렉토리를 가져온다. HOME이 없을 시 error 프린트
                fprintf(stderr, "%s: home directory does not existed\n", strerror(errno));
        }
        else {
                if (access(".ishrc", 0) == -1){         //ishrc라는 고정된 값을 확인해본다. access는 있을 시 0, 없을
 시 -1을 리턴하며 2번째 인자를 0으로 넘으로써 파일이 있는지 확인하는 기능으로 사용
                        fprintf(stderr, "%s: ishrc file does not existed\n", strerror(errno));
                }
                else {
                        fp = fopen(".ishrc", "r");
                        while(!feof(fp)) {
                                if(fgets(command_line, 1024, fp) != NULL){

                fprintf(stdout, "%% %s", command_line); // command_line 마지막에  \n이 있기에 따로 \n을 넣어주지 않>아도 된다.

        DynArray_T token_array = DynArray_new(0);       // Token들을 담을 Dynamic Array를 생성
        if (lex_line(program_name, command_line, token_array)){
                if (parse_tokens(program_name, token_array)) {
                        execute_parsed_tokens(program_name, token_array);
                }
        //      else {
        //              fprintf(stderr, "%s: Invalid Parsing\n", program_name);
        //      }
        }
        else {
                fprintf(stderr, "%s: Invalid line\n", program_name);
        }
                                }
                                for (int i = 0; i<1024; i++)
                                        command_line[i] = 0;
                        }
                }
        }

        while (1) {
        DynArray_T token_array = DynArray_new(0);       // Token들을 담을 Dynamic Array를 생성
                fprintf(stdout, "%% ");
                if (fgets(command_line, 1024, stdin) != NULL) {
                        printf("%s ", command_line);

        if (lex_line(program_name, command_line, token_array)){
                if (parse_tokens(program_name, token_array)) {
                        execute_parsed_tokens(program_name, token_array);
                }
        //      else {
        //              fprintf(stderr, "%s: Invalid Parsing\n", program_name);
        //      }
        }
        else {
                fprintf(stderr, "%s: Invalid line\n", program_name);
        }
                }
                else {
                        exit(EXIT_SUCCESS);
                }
                                for (int i = 0; i<1024; i++)
                                        command_line[i] = 0;
        }
}