#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "pprint.h"

/**
 * Main function
 * Includes infinite loop to get user input, quits on "exit" command
 */
int main(int argc, char *argv[]){
    // input buffer, initialize to NULL so getline() allocates
    size_t buffer_size = 0;
    char *buffer = NULL;

    // token array, should probably initialize to NULL allocate in lexer
    char **tokens = malloc(sizeof(char*) * MAX_TOKEN_CNT);

    while (1){
        // get input
        pprint_prompt();
        getline(&buffer, &buffer_size, stdin); // vulnerable to DoS attack

        // lexer, fills tokens
        lexer(buffer, tokens);

        // check for different commands
        
        // empty command
        if (tokens[0] == NULL){
            continue;
        } 
        // exit command
        else if (!strcmp(tokens[0], "exit")) {
            break;
        }
        
        // free tokens
        for (int i=0; i<MAX_TOKEN_CNT; i++){
            free(tokens[i]);
        }
    }

    // free everything
    free(buffer);
    for (int i=0; i<MAX_TOKEN_CNT; i++){
        free(tokens[i]);
    }
    free(tokens);

    return(0);
}