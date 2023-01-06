#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* Fork and exec 
* set "unknown" to 1 if executable does not exits
*/
void exec(char **tokens, int *unknown){
    int child_exit_status;
    *unknown = 1;

    // fork and exec
    pid_t pid = fork();

    // child
    if (pid == 0) {
        execvp(*tokens, tokens);
    }

    // parent
    int rc = waitpid(0, &child_exit_status, 0);
    if (rc != -1){
        *unknown = 0;
    }
}