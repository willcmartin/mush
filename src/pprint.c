#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pprint.h"

#define NAME_LEN 32
#define PATH_LEN 64
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

/**
* Who likes pretty printing? I like pretty printing
*/
void pprint_prompt(){
    char username[NAME_LEN];
    char hostname[NAME_LEN];
    char curr_path[PATH_LEN];

    char *token;
    size_t length;

    // TODO: deal with errors
    getlogin_r(username, sizeof(username));
    gethostname(hostname, sizeof(hostname));
    getcwd(curr_path, sizeof(curr_path));

    // split hostname on ., my mac adds weird stuff sometimes
    token = strchr(hostname, '.');
    *token = '\0';

    // split curr_path on /
    token = strrchr(curr_path, '/');
    length = strlen(token);
    memcpy(curr_path, token+1, length);

    printf(CYN "MUSH " RESET "%s" CYN "@" RESET "%s" CYN " :: " YEL "%s" CYN " >> " RESET, username, hostname, curr_path);
}