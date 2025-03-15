#include "../inc/minishell.h"

void    add_env_node(s_env **env_list, char *key, char *value)
{
    s_env   *new_node;

    new_node = safe_malloc(sizeof(s_env));
    new_node->key = key;
    new_node->value = value;
    new_node->next = *env_list;
    *env_list = new_node;
}

void    add_token_node(s_token **token_list, char *key, char *code)
{
    s_token  *new_node;

    new_node = safe_malloc(sizeof(s_token));
    new_node->type = code;
    new_node->value = key;
    new_node->next = *token_list;
    *token_list = new_node;
}