/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:14 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/02 14:21:23 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clear_env(s_env **env)
{
	s_env	*temp;

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

void	clear_token(s_token **token)
{
	s_token	*temp;

	temp = NULL;
	if (token)
	{
		while (*token)
		{
			temp = (*token)->next;
			free(*token);
			*token = temp;
		}
	}
}

void	clear_tree(s_tree **tree)
{
	int	i;

	if (!tree || !*tree)
		return ;
	clear_tree(&(*tree)->left);
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

void	ft_exit(s_minishell *mini, char *error)
{
	if (mini->created)
		free_mini_struct(mini);
	if (error)
		printf(RED "%s\n" RESET, error);
	clear_history();
	free(mini);
	exit(1);
}
