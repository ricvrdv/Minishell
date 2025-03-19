#include "../../inc/minishell.h"

void    add_env_node(s_env **env_list, char *key, char *value)
{
    s_env   *new_node;

    new_node = safe_malloc(sizeof(s_env));
    new_node->key = key;
    new_node->value = value;
    new_node->next = *env_list;
    *env_list = new_node;
}

void add_token_node(s_token **tokens, s_token *new_token)
{
    s_token *last;

    if (!new_token) // Always check if new_token is valid
        return;

    if (!*tokens)   // Check if the token list is empty
        *tokens = new_token;
    else
    {
        last = *tokens;
        while (last->next)
            last = last->next;
        last->next = new_token;
    }
}
void    add_args_node(s_args **args_list, char *key)
{
    s_args  *new_node;

    new_node = safe_malloc(sizeof(s_args));
    new_node->value = key;
    new_node->next = *args_list;
    *args_list = new_node;
}
