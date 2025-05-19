/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:52:04 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env	*create_env_node(const char *key, const char *value);

void	update_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*var;
	t_env	*new_var;

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

t_env	*find_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

static t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
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
	ft_putstr_fd("Minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	handle_exit_cleanup(t_minishell *mini, int code)
{
	ft_exit_child(mini, NULL);
	close_fds();
	exit_code(code, 1, 1);
}
