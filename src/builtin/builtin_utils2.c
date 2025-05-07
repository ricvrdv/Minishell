/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:39:40 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/07 15:39:57 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sync_env_array(s_minishell *mini)
{
	s_env	*current;
	int		count;

	if (!mini)
		return ;
	free_array(mini->env_array);
	current = mini->env;
	count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	mini->env_array = build_env_array(mini->env, count);
}

static char	**build_env_array(s_env *env, int count)
{
	char	**array;
	int		i;

	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
			array[i] = join_key_value(env);
		else
			array[i] = ft_strdup(env->key);
		if (!array[i])
		{
			free_array(array);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	array[i] = NULL;
	return (array);
}

static char	*join_key_value(s_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
