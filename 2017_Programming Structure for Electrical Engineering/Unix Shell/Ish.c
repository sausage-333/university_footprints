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


static int sigquit_exit_flag = 0; //quit�ñ׳��� ������ 1, alarm�� ������ 0�� ���� 5�ʸ� ��Ʈ
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
        if (sigquit_exit_flag){ //5�� �̳��� 1�� �� �ҷȴٸ�, alarm�� �Ϸᰡ ���� ���߱⿡ ���°� 1�ϰ�.
                exit(EXIT_SUCCESS);
        }
        fprintf(stdout, "\nType Ctrl-\\ again within 5 seconds to exit.\n");
        sigquit_exit_flag = !sigquit_exit_flag;
        alarm(5);
}


static void sigalarm_handler(int sig){
        sigquit_exit_flag = !sigquit_exit_flag; //5���� alarm�� ������ �ٽ� quit�� 2�� ������ �����Բ� �� �� �ֵ���.
}


void execution(char program_name[], char* command_line, FILE *fp, int is_file_read) {
        DynArray_T token_array = DynArray_new(0);       // Token���� ���� Dynamic Array�� ����

        if (is_file_read){              //File read������ %% %s�� ���ش�. ������ �ƴ� ��, �̸� %�� �ϸ鼭 ����Ʈ �� �ʿ䰡 ����.
                fprintf(stdout, "%% %s", command_line); // command_line ��������  \n�� �ֱ⿡ ���� \n�� �־����� ��>�Ƶ� �ȴ�.
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

        sigemptyset(&set);      //Signal Set���� �� �������� ��, �ʿ��� Signal�� �־��ְ� procmask�� ���� unblock�� �������ش�.
        sigaddset(&set, SIGINT);
        signal(SIGINT, SIG_IGN);
        sigaddset(&set, SIGALRM);
        signal(SIGALRM, sigalarm_handler);
        sigaddset(&set, SIGQUIT);
        signal(SIGQUIT, sigquit_handler);
        sigprocmask(SIG_UNBLOCK, &set, NULL);


        program_name = argv[0];

        if(chdir(getenv("HOME")) == -1) {       //HOME�� ���� ���丮�� �����´�. HOME�� ���� �� error ����Ʈ
                fprintf(stderr, "%s: home directory does not existed\n", strerror(errno));
        }
        else {
                if (access(".ishrc", 0) == -1){         //ishrc��� ������ ���� Ȯ���غ���. access�� ���� �� 0, ����
 �� -1�� �����ϸ� 2��° ���ڸ� 0���� �����ν� ������ �ִ��� Ȯ���ϴ� ������� ���
                        fprintf(stderr, "%s: ishrc file does not existed\n", strerror(errno));
                }
                else {
                        fp = fopen(".ishrc", "r");
                        while(!feof(fp)) {
                                if(fgets(command_line, 1024, fp) != NULL){

                fprintf(stdout, "%% %s", command_line); // command_line ��������  \n�� �ֱ⿡ ���� \n�� �־����� ��>�Ƶ� �ȴ�.

        DynArray_T token_array = DynArray_new(0);       // Token���� ���� Dynamic Array�� ����
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
        DynArray_T token_array = DynArray_new(0);       // Token���� ���� Dynamic Array�� ����
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