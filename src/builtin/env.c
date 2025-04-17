#include "../../inc/minishell.h"

int    mini_env(s_minishell *mini, s_tree *node)
{
    s_env   *current;

    current = mini->env;
    if (node->argcount > 1)
    {
        ft_putstr_fd("This version does not handle options or arguments.\n", 2);
        return (1);
    }
    while (current)
    {
        if (current->value)
        {
            ft_putstr_fd(current->key, STDOUT_FILENO);
            ft_putstr_fd("=", STDOUT_FILENO);
            ft_putstr_fd(current->value, STDOUT_FILENO);
            ft_putstr_fd("\n", STDOUT_FILENO);
        }
        current = current->next;
    }
    sync_env_array(mini);
    return (0);
}