#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mush.h"
#include "lexer.h"
#include "parser.h"

// might be more efficient to not have separate node and token
// structs and instead have one struct that is only partially
// filled by the lexer and the completed by the parser to 
// create a node

// set of functions that deal with terminals
static int parse_exec(struct node* parent, struct buffer *buf)
{
    // save all following tokens as children of parent

    // first child
    // TODO: make function to create new node
    struct token *tok = lexer(buf);
    struct node *first_child = malloc(sizeof(struct node));
    memset(first_child, 0, sizeof(*first_child));

    first_child->type = NODE_VAR;
    first_child->val.vstr = tok->text;

    parent->first_child = first_child;

    // siblings (refactor to be more elegant?)
    tok = lexer(buf);
    while (tok->type != TOKEN_EOL){
        struct node *next_sibling = malloc(sizeof(struct node));
        memset(next_sibling, 0, sizeof(*next_sibling));

        first_child->type = NODE_VAR;
        first_child->val.vstr = tok->text;

        parent->next_sibling = next_sibling;
        parent = next_sibling;

        tok = lexer(buf);
    }

    return 1;
}

// this function deals with non-terminals
int parse(struct node* root, struct buffer *buf)
{
    // get token
    struct token *tok = lexer(buf);

    // check type of token

    // executable
    if (tok->type == TOKEN_UNKOWN) {
        root->val.vstr = tok->text;
        root->type = NODE_EXEC;

        parse_exec(root, buf);
    } else {
        printf("not implemented\n");
    }

    return 1;
}
