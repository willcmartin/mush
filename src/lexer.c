#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mush.h"
#include "lexer.h"

/*
 * Checks if first character in buffer is white space
 * return 1 if buf begins with a white space character
 */
static int begins_with_whitespace(char *buf_text)
{
    static char whitespace[] = {' ', '\n'};
    static int whitespace_count = 2;

    for (int i=0; i<whitespace_count; i++) {
        if (buf_text[0] == whitespace[i]) {
            return 1;
        }
    }

    return 0;
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
struct token *lexer(struct buffer *buf)
{
    printf("%s\n", buf->buf_curr);

    // allocate token 
    struct token *tok = malloc(sizeof(struct token));
    if (!tok) { 
        return NULL;
    }
    memset(tok, 0, sizeof(*tok));

    // initial token length, initialize buffer
    tok->len = 0;
    char *tok_text_buffer = malloc((tok->len+1)*sizeof(char));
    int tok_text_buffer_len = tok->len+1

    // loop over characters in buffer until white space
    // fill token text buffer
    if (!begins_with_whitespace(buf->buf_curr)) {
        tok->len++:
        if (tok->len > tok_text_buffer_len){
            
        }
    }

    // text terminating character
    tok->text[tok->len+1] = '/0';

    return tok;

}


// const char delim[6] = " \n\t\a\r";

// char *token = strtok(buffer, delim);
// int token_num = 0;
// while(token != NULL) {
//     if (token_num >= MAX_TOKEN_CNT) {
//         fprintf(stderr, "too many tokens\n");
//         exit(0);
//     }

//     tokens[token_num] = strdup(token);
//     token_num++;
//     token = strtok(NULL, delim);
// }
// tokens[token_num] = NULL;