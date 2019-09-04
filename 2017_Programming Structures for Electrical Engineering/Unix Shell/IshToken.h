
#include "dynarray.h"
void make_operator_token(char program_name[], DynArray_T token_array, char *token_name);

void make_token(char program_name[], DynArray_T token_array, char *token_name);

int lex_line(char program_name[], char command_line[], DynArray_T token_array);

int parse_tokens(char program_name[], DynArray_T token_array);

int get_redirection_token_index(char* command_line[], int command_length);

void redirection_command_line(
	char program_name[], 
	char* command_line[],
	int command_length, 
	int redirection_token_index
);

void execute_parsed_tokens(char program_name[], DynArray_T token_array);

void fprintf_error_message_with_program_name(char program_name[], char error_message[]);
