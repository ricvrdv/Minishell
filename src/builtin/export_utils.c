/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:47 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:52:04 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	**env_list_to_array(t_env *env, int count);
static void		sort_env_array(t_env **array, int count);
static void		print_env_entry(t_env *env);

void	print_sorted_env(t_env *env)
{
	int		count;
	int		i;
	t_env	**array;
	t_env	*head;

	head = env;
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	array = env_list_to_array(head, count);
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

static t_env	**env_list_to_array(t_env *env, int count)
{
	t_env	**array;
	int		i;

	array = malloc(count * sizeof(t_env *));
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

static void	sort_env_array(t_env **array, int count)
{
	t_env	*temp;
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

static void	print_env_entry(t_env *env)
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
	const char *ptr;
	
	ptr = str;
	if (!str || !*str)
		return (0);
	if (*ptr == '=')
		return (0);
	if (!ft_isalpha(*ptr) && *ptr != '_')
		return (0);
	while (*++ptr && *ptr != '+' && *ptr != '=')
	{
		if (!ft_isalnum(*ptr) && *ptr != '_')
			return (0);
	}
	return (1);
}
