#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

#define BUFF_SIZE 256

/**
 * Main function
 */
int main(int argc, char *argv[]){
    // input buffer
    size_t buffer_size = BUFF_SIZE;
    char *buffer = malloc(sizeof(char) * buffer_size);

    while (1){
        // get input
        printf("mush $ ");
        getline(&buffer, &buffer_size, stdin);

        // lexer
        char **tokens = lexer(buffer);
        
        free(tokens);
    }

    free(buffer);

    return(0);
}