#include "../../inc/minishell.h"

s_tree *new_tree_node(s_type type)
{
    s_tree *node;
    
    node = safe_malloc(sizeof(s_tree));
    node->type = type;
    node->argcount = 0;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

s_tree	*create_arg_node(s_token *token)
{
    s_tree  *node;

    node = safe_malloc(sizeof(s_tree));
    node->type = token->type;
    node->argcount = 0;
    node->args = safe_malloc(sizeof(char *) * 2);
    node->args[0] = token->value;
    node->args[1] = NULL;
    node->left = NULL;
    node->right = NULL;
    free(token);
    return (node);
}

s_tree  *create_redirection_node(s_token **tokens, s_token *temp)
{
    s_tree  *redi_node;

    redi_node = new_tree_node((*tokens)->type);
    *tokens = (*tokens)->next->next;
    redi_node->left = parse_redirect(tokens);
    redi_node->right = create_arg_node(temp->next); 
    redi_node->argcount = 0;
    free(temp->value);
    free(temp);
    return (redi_node);
}