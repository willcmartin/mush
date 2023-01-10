#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "mush.h"

// this function sucks
// delete it asap
void print_ast(struct node *root)
{
    printf("%s\n", root->val.vstr);
    while (root->first_child != NULL) {
        printf("%s\n", root->first_child->val.vstr);
        while (root->next_sibling != NULL) {
            printf("%s\n", root->next_sibling->val.vstr);
            root = root->next_sibling;
        }

    }
}