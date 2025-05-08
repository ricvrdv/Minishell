/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:06:26 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/07 15:39:23 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static s_env	*create_env_node(const char *key, const char *value);

void	update_env_var(s_env **env, const char *key, const char *value)
{
	s_env	*var;
	s_env	*new_var;

	var = find_env_var(*env, key);
	if (var)
	{
		free(var->value);
		if (value)
			var->value = ft_strdup(value);
		else
			var->value = NULL;
		if (value && !var->value)
			exit(EXIT_FAILURE);
	}
	else
	{
		new_var = create_env_node(key, value);
		new_var->next = *env;
		*env = new_var;
	}
}

s_env	*find_env_var(s_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static s_env	*create_env_node(const char *key, const char *value)
{
	s_env	*new;

	new = malloc(sizeof(s_env));
	if (!new)
		exit(EXIT_FAILURE);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	if (!new->key || (value && !new->value))
	{
		free(new->key);
		free(new->value);
		free(new);
		exit(EXIT_FAILURE);
	}
	new->next = NULL;
	return (new);
}

void	handle_invalid_identifier(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
