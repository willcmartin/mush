#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_CNT 64

/**
 * Lexer, separates tokens
 * 
 * @param input input string following "prompt > "
 * @return array of strings split by white space
 */
char **lexer(char *buffer){
    const char delim[6] = " \n\t\a\r";
    char **tokens = malloc(sizeof(char*) * TOKEN_CNT);

    char *token = strtok(buffer, delim);
    int token_num = 0;
    while(token != NULL) {
        tokens[token_num] = strdup(token);
        token_num++;
        token = strtok(NULL, delim);
    }
    tokens[token_num] = NULL;

    return tokens;
}