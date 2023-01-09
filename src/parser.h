#ifndef PARSER_H
#define PARSER_H

enum node_type {
    NODE_EXEC,
    NODE_VAR
};

union node_val {
    int vint;
    char *vstring;
};

struct node {
    enum node_type type;
    union node_val val;
    struct node *first_child;
    struct node *next_sibling;
};

/*
Generate a AST recursively
Return the root node, error on syntax error
Branches for each non-terminal, create leaf for each terminal
Pass current root node 

First goal: executable

executable name (NODE_EXEC)
|
first tag (NODE_VAR) -- second tag (NODE_VAR) -- ...
*/

int parse(struct node* root, struct buffer *buf);

#endif