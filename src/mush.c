#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mush.h" 
#include "lexer.h"
#include "pprint.h"
#include "builtin.h"
#include "exec.h"
#include "parser.h"
#include "debug.h"

#define MAX_PATH_LEN 10


/**
 * Main function
 * Includes infinite loop to get user input, quits on "exit" command
 */
int main(int argc, char *argv[])
{
    // input buffer, initialize to NULL so getline() allocates
    struct buffer *buf = malloc(sizeof(struct buffer));
    memset(buf, 0, sizeof(*buf));

    int unknown = 0;

    while (1) {
        // get input
        pprint_prompt();
        getline(&buf->buf_curr, &buf->len, stdin); // vulnerable to DoS attack

        // create ast using parser, the parser gets tokens from the lexer
        struct node *root = malloc(sizeof(struct node));
        memset(root, 0, sizeof(*root));
        parse(root, buf);

        print_ast(root);

        // lexer produces tokens
        // struct token *tok = lexer(buf);

        // clear buffer
        memset(buf, 0, sizeof(*buf));
    }

    free(buf);
    // TODO free buf_curr

    return(0);
}