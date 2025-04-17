#include "../../inc/minishell.h"

void	error_exit(char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(1);
}

void	free_mini_struct(s_minishell *mini)
{
	if (mini->cur_dir)
		free(mini->cur_dir);
	if (mini->env_array)
		clear_env_array(&mini->env_array);
	if (mini->env)
		clear_env(&mini->env);
}

char	*get_dir()
{
	char	*currentdir;

	currentdir = getcwd(NULL, 1024);
	return (currentdir);
}

void	free_stuff(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_struct(s_minishell *mini)
{
	if (mini->cur_dir)
		free(mini->cur_dir);
	if (mini->env_array)
		clear_env_array(&mini->env_array);
	if (mini->env)
		clear_env(&mini->env);
}

