/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:54 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 13:19:55 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	remove_env_var(s_env **env, const char *key);

int	mini_unset(s_minishell *mini, s_tree *node)
{
	int	i;

	if (!mini || !node)
		return (0);
	i = 1;
	while (i < node->argcount)
	{
		remove_env_var(&mini->env, node->args[i]);
		i++;
	}
	sync_env_array(mini);
	return (0);
}

static void	remove_env_var(s_env **env, const char *key)
{
	s_env	*current;
	s_env	*prev;

	if (!env || !*env || !key)
		return ;
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
