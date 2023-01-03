#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NAME_LEN 16
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

    getlogin_r(username, sizeof(username));
    gethostname(hostname, sizeof(hostname));

    // split hostname on period, my mac adds weird stuff sometimes
    for (int i=0; i<NAME_LEN; i++){
        if (hostname[i] == '.') {
            hostname[i] = '\0';
            break;
        }
    }

    printf(CYN "MUSH " RESET "%s" CYN "@" RESET "%s " CYN ">> " RESET, username, hostname);
}