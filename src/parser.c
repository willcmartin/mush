#include "mush.h"
#include "lexer.h"

// int parse(struct buffer *buf)
// {
//     struct node *root = malloc(sizeof(struct node));
//     memset(root, 0, sizeof(*root));
//     parse_tree(root);
// }

int parse_exec(struct node* parent, struct buffer *buf)
{
    
}

int parse(struct node* root, struct buffer *buf)
{
    // get token
    struct token *tok = lexer(buf)

    // check type of token

    // executable name
    if (tok->token_type == TOKEN_UNKOWN) {
        root->type = NODE_EXEC;
    }
}
