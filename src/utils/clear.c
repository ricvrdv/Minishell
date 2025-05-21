/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:14 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 18:14:00 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_env(t_env **env)
{
	t_env	*temp;

	temp = NULL;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = temp;
	}
}

void	clear_token(t_token **token)
{
	t_token	*temp;

	if (token && *token)
	{
		while (*token)
		{
			temp = (*token)->next;
			free(*token);
			*token = temp;
		}
		*token = NULL;
	}
}

void	clear_tree(t_tree **tree)
{
	int	i;

	if (!tree || !*tree)
		return ;
	if ((*tree)->left)
		clear_tree(&(*tree)->left);
	if ((*tree)->right)
		clear_tree(&(*tree)->right);
	if ((*tree)->args)
	{
		i = 0;
		while ((*tree)->args[i])
		{
			free((*tree)->args[i]);
			i++;
		}
		free((*tree)->args);
	}
	if ((*tree)->hd_file)
	{
		free((*tree)->hd_file);
		(*tree)->hd_file = NULL;
	}
	free(*tree);
	*tree = NULL;
}

void	clear_env_array(char ***env_array)
{
	int	i;

	i = 0;
	while ((*env_array)[i])
	{
		free((*env_array)[i]);
		i++;
	}
	free(*env_array);
	*env_array = NULL;
}

void	ft_exit(t_minishell *mini, char *error)
{
	if (mini->created)
		free_mini_struct(mini);
	if (error)
		printf(RED "%s\n" RESET, error);
	rl_clear_history();
	free(mini);
	exit_code(0, 0, 1);
}
