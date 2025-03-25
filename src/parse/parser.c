#include "../../inc/minishell.h"

s_tree  *parse_pipe(s_token **tokens)
{
    s_token *temp;
    s_token *next_token;
    s_tree  *pipe;

    temp = *tokens;
    while(*tokens && (*tokens)->next)
    {
        next_token = (*tokens)->next;
        if((*tokens)->next->type == PIPE)   //FOUND A PIPE IN OUR CMD LIST
        {
            pipe = new_tree_node((*tokens)->next->type);
            (*tokens)->next = NULL;
            pipe->left = parse_redirect();
            pipe->right = parse_pipe(&(next_token->next));
            free(next_token->value);
            free(next_token);
            return (pipe);
        } 
        *tokens = next_token;
    }
    return (parse_redirect(&temp));
}

s_tree  parse_redirect(s_token **tokens)
{
    s_token *temp;
    s_token *next_token;
    s_tree  *pipe;

    temp = *tokens;
    if((*tokens)->type >= REDIRECT_L)   //FOUND A PIPE IN OUR CMD LIST
}