#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mush.h"
#include "lexer.h"

static char *keywords[] = {};
static char whitespace[] = {'\n', ' ', '\t'};
static char eol[] = {'\0'};

static int keywords_cnt = sizeof(keywords) / sizeof(char *);
static int whitespace_cnt = sizeof(whitespace);
static int eol_cnt = sizeof(eol);

/*
 * Checks if first character in buffer is white space
 * return 1 if buf begins with a white space character
 */
static int begins_with_whitespace(char *buf_text)
{
    for (int i=0; i<whitespace_cnt; i++) {
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
 *
 */
struct token *lexer(struct buffer *buf)
{
    // allocate token 
    struct token *tok = malloc(sizeof(struct token));
    if (!tok) { 
        return NULL;
    }
    memset(tok, 0, sizeof(*tok));

    // advance to fist none whitespace
    while (begins_with_whitespace(buf->buf_curr + tok->len)) {
        buf->buf_curr++;
    }

    // get token length and text
    tok->len = 0;
    while (!begins_with_whitespace(buf->buf_curr + tok->len)) {
        tok->len++;
    }
    tok->text = strndup(buf->buf_curr, tok->len); // TODO: free

    if (!tok->text){
        return NULL;
    }

    // get token type
    for (int i=0 ; i<keywords_cnt; i++) {
        if (!strcmp(tok->text, keywords[i])) {
            ; // TODO
        }
    }
    for (int i=0; i<eol_cnt; i++) {
        if (tok->text[0] == eol[i]) {
            tok->type = TOKEN_EOL;
        }
    }
    if (!tok->type) {
        tok->type = TOKEN_UNKOWN;
    }

    // update current buffer pointer
    buf->buf_curr += tok->len;

    return tok;
}
