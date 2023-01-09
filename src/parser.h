#ifndef PARSER_H
#define PARSER_H

enum node_type {
    NODE_EXEC,
    NODE_VAR
};

struct node {
    enum node_type type;
};

#endif