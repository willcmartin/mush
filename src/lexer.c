#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

/**
 * Lexer, separates tokens
 * 
 * @param input input string following "prompt > "
 * @return array of strings split by white space
 */
void lexer(char *buffer, char **tokens){
    const char delim[6] = " \n\t\a\r";

    char *token = strtok(buffer, delim);
    int token_num = 0;
    while(token != NULL) {
        if (token_num >= MAX_TOKEN_CNT){
            fprintf(stderr, "too many tokens\n");
            exit(0);
        }

        tokens[token_num] = strdup(token);
        token_num++;
        token = strtok(NULL, delim);
    }
    tokens[token_num] = NULL;
}