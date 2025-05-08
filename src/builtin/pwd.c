#include "../../inc/minishell.h"

int	mini_pwd(s_minishell *mini)
{
	if (mini->cur_dir)
	{
		ft_putstr_fd(mini->cur_dir, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	else
		return (1);
}
