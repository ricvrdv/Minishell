#include "../../inc/minishell.h"

static  void remove_env_var(s_env **env, const char *key);

void    mini_unset(s_minishell *mini, s_tree *node)
{
    int i;
    
    if (!mini || !node)
    {
        ft_putstr_fd("minishell: unset: invalid arguments\n", STDERR_FILENO);
        return ;
    }
    i = 1;
    while (i < node->argcount)
    {
        remove_env_var(&mini->env, node->args[i]);
        i++;
    }
    sync_env_array(mini);
}

static  void remove_env_var(s_env **env, const char *key)
{
    s_env *current;
    s_env *prev;

    if (!env || !*env || !key)
        return;
    current = *env;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}