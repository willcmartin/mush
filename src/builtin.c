#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#import "builtin.h"

/**
* change directory built-in command
*/
void cd(char **tokens){
    // error if 0 or >1 commands
    if ((tokens[1] == NULL) || (tokens[2] != NULL)){
        printf("cd: too many/too few arguments\n");
        return;
    }
    
    // change dir sys call
    int chdir_err = chdir(tokens[1]);
    if (chdir_err == -1){
        printf("cd: directory does not exist\n");
        return;
    }
}