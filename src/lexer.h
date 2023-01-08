#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_CNT 64

enum token_type {
    TOKEN_UNKOWN,         // exec name, exec flags
};

struct token {
    enum token_type type;
    char *text;
    int len;
};

struct token *lexer(struct buffer *buf);

#endif