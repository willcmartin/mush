#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mush.h" 
#include "lexer.h"
#include "pprint.h"
#include "builtin.h"
#include "exec.h"

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

    // size_t buffer_size = 0;
    // char *buffer_raw = NULL;
    

    // token array, should probably initialize to NULL allocate in lexer
    // TODO: could probably avoid the malloc completely unless want an expectable array of strings
    // char **tokens = malloc(sizeof(char*) * MAX_TOKEN_CNT);

    int unknown = 0;

    while (1) {
        // get input
        pprint_prompt();
        getline(&buf->buf_curr, &buf->len, stdin); // vulnerable to DoS attack        

        // lexer produces tokens
        printf("hello\n");
        struct token *tok = lexer(buf);

        printf("%d\n", tok->type);

        // clear buffer
        memset(buf, 0, sizeof(*buf));
    }

    free(buf);

    return(0);
}