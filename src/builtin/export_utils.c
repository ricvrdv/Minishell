/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:09:50 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/07 13:14:57 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static s_env	**env_list_to_array(s_env *env, int count);
static void		sort_env_array(s_env **array, int count);
static void		print_env_entry(s_env *env);

void	print_sorted_env(s_env *env)
{
	int		count;
	int		i;
	s_env	**array;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	array = env_list_to_array(env, count);
	if (!array)
		return ;
	sort_env_array(array, count);
	i = 0;
	while (i < count)
	{
		print_env_entry(array[i]);
		i++;
	}
	free(array);
}

static s_env	**env_list_to_array(s_env *env, int count)
{
	s_env	**array;
	int		i;

	array = malloc(count * sizeof(s_env *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		array[i] = env;
		env = env->next;
		i++;
	}
	return (array);
}

static void	sort_env_array(s_env **array, int count)
{
	s_env	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_env_entry(s_env *env)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	is_valid_identifier(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '=')
		return (0);
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*++str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
	}
	return (1);
}
