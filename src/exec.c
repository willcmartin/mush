#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
* Fork and exec 
* set "unknown" to 1 if executable does not exits
*/
void exec(char **path, int path_len, char **tokens, int *unknown){
    int child_exit_status;
    *unknown = 1;

    // loop over path vars
    for (int i=0; i<path_len; i++){
        // get full path to exec
        // assume that path variable include trailing backslash
        char *full_path = malloc(strlen(path[i]) + strlen(tokens[0]) + 1);
        strcpy(stpcpy(full_path, path[i]), tokens[0]);

        // fork and exec
        if (!access(full_path, X_OK)){
            pid_t pid = fork();

            // child
            if (pid == 0) {
                execv(full_path, tokens);
            }
            
            // parent
            waitpid(0, &child_exit_status, 0);
            *unknown = 0;
        }
    }    
}