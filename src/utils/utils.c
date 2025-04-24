/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/24 15:08:41 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
//can remove 
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

void	free_split(char **arr)
{
	int i = 0;
	if (!arr)
		return;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}