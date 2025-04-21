/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:52:08 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 16:31:07 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	append_value_to_result(char **res_ptr, const char *value)
{
	if (value)
	{
		ft_strcpy(*res_ptr, value);
		*res_ptr += ft_strlen(value);
	}
}

void	get_variable_name(const char **ptr, char *var_name)
{
	int	i;

	i = 0;
	(*ptr)++;
	if (**ptr == '?')
	{
		var_name[i++] = '?';
		(*ptr)++;
	}
	else
	{
		while (isalnum(**ptr) || **ptr == '_')
		{
			var_name[i++] = **ptr;
			(*ptr)++;
		}
	}
	var_name[i] = '\0';
}

char	*find_variable(s_minishell *mini, const char *variable)
{
	s_env	*env;
	int		len;
	char	*exit_status;

	len = ft_strlen(variable);
	if (ft_strcmp(variable, "?") == 0)
	{
		exit_status = ft_itoa(exit_code(0, 0, 0));
		return (exit_status);
	}
	env = mini->env;
	while (env)
	{
		if (ft_strncmp(env->key, variable, len + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

bool	enclosed_single_quotes(const char *str)
{
	size_t	len;

	len = strlen(str);
	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'')
		return (true);
	return (false);
}

bool	should_expand(const char *str)
{
	if (!str)
		return (false);
	if (enclosed_single_quotes(str))
		return (false);
	return (true);
}
