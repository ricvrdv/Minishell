/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:27 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:52:04 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char		**build_env_array(t_env *env, int count);
static char		*join_key_value(t_env *env);

void	sync_env_array(t_minishell *mini)
{
	t_env	*current;
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

static char	**build_env_array(t_env *env, int count)
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

static char	*join_key_value(t_env *env)
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
