#ifndef LEXER_H
#define LEXER_H

enum token_type {
    TOKEN_UNKOWN,         // exec name, exec flags
    TOKEN_EMPTY,          // whitespace
    TOKEN_EOL,            // newline char
};

struct token {
    enum token_type type;
    char *text;
    int len;
};

struct token *lexer(struct buffer *buf);

#endif