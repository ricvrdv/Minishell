/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:02:05 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/07 14:09:47 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	export_argument(s_minishell *mini, char *arg);
static int	append_to_env_var(s_minishell *mini, char *arg, char *plus_sign);
static int	assign_env_var(s_minishell *mini, char *arg, char *equal_sign);
static int	to_existing_or_create(s_minishell *mini, char *key, char *value);

int	mini_export(s_minishell *mini, s_tree *node)
{
	int	i;
	int	status;

	if (node->argcount == 1)
	{
		print_sorted_env(mini->env);
		return (0);
	}
	status = 0;
	i = 1;
	while (i < node->argcount)
	{
		if (!export_argument(mini, node->args[i]))
			status = 1;
		i++;
	}
	sync_env_array(mini);
	return (status);
}

static int	export_argument(s_minishell *mini, char *arg)
{
	char	*equal_sign;
	char	*plus_sign;

	if (!arg)
		return (0);
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign || *arg == '=')
	{
		if (!is_valid_identifier(arg))
		{
			handle_invalid_identifier(arg);
			return (0);
		}
		if (!find_env_var(mini->env, arg))
			add_env_node(&mini->env, ft_strdup(arg), NULL);
		return (1);
	}
	plus_sign = ft_strchr(arg, '+');
	if (plus_sign && plus_sign + 1 == equal_sign)
		return (append_to_env_var(mini, arg, plus_sign));
	else
		return (assign_env_var(mini, arg, equal_sign));
}

static int	to_existing_or_create(s_minishell *mini, char *key, char *value)
{
	s_env	*var;
	char	*new_value;

	var = find_env_var(mini->env, key);
	if (var)
	{
		new_value = ft_strjoin(var->value, value);
		if (!new_value)
			return (free(key), free(value), 0);
		free(var->value);
		var->value = new_value;
	}
	else
		update_env_var(&mini->env, key, value);
	free(key);
	free(value);
	return (1);
}

static int	append_to_env_var(s_minishell *mini, char *arg, char *plus_sign)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, plus_sign - arg);
	value = ft_strdup(plus_sign + 2);
	if (!key || !value)
		return (free(key), free(value), 0);
	if (!is_valid_identifier(key))
	{
		handle_invalid_identifier(key);
		return (free(key), free(value), 0);
	}
	return (to_existing_or_create(mini, key, value));
}

static int	assign_env_var(s_minishell *mini, char *arg, char *equal_sign)
{
	char	*key;
	char	*value;
	int		return_value;

	return_value = 1;
	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (!key || !value)
		return (free(key), free(value), 0);
	if (*key == '\0')
	{
		free(key);
		key = ft_strdup(arg);
		free(value);
		return_value = 0;
	}
	if (return_value && !is_valid_identifier(key))
	{
		handle_invalid_identifier(arg);
		return (free(key), free(value), 0);
	}
	if (return_value)
		update_env_var(&mini->env, key, value);
	return (free(key), free(value), return_value);
}
