#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

struct token {
    char *value;
}

/*
 * The lexer separates a buffer string into tokens
 * 
 * Takes buffer struct as input
 * Returns next token struct following pointer in buffer
 * Returns null if EOL
 *
 * TODO:
 * - how to deal with multiple EOL character (&& and batch)
 */
void lexer(char *buffer, char **tokens)
{
    const char delim[6] = " \n\t\a\r";

    char *token = strtok(buffer, delim);
    int token_num = 0;
    while(token != NULL) {
        if (token_num >= MAX_TOKEN_CNT) {
            fprintf(stderr, "too many tokens\n");
            exit(0);
        }

        tokens[token_num] = strdup(token);
        token_num++;
        token = strtok(NULL, delim);
    }
    tokens[token_num] = NULL;
}