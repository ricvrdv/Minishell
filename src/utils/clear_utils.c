/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:24 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/15 16:39:09 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_mini_struct(s_minishell *mini)
{
	if (mini->cur_dir)
		free(mini->cur_dir);
	if (mini->env_array)
		clear_env_array(&mini->env_array);
	if (mini->env)
		clear_env(&mini->env);
	if (mini->root)
		clear_tree(&mini->root);
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
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	clean_args_expand(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (args[i] != NULL)
		{
			args[j++] = args[i];
		}
		i++;
	}
	args[j] = NULL;
}

void	pre_clean_args(char **args, int *argcount)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		if (args[i] == NULL || ft_strcmp(args[i], "") == 0)
		{
			free(args[i]);
			(*argcount)--;
		}
		else
			args[j++] = args[i];
		i++;
	}
	args[j] = NULL;
}
