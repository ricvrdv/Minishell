#include "../../inc/minishell.h"

void mini_pwd(s_minishell *mini)
{
    if (mini->cur_dir)
    {
        ft_putstr_fd(mini->cur_dir, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        mini->exit_status = 0;
    }
    else
        mini->exit_status = 1;
}