/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:52:12 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/28 00:45:39 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_tree(s_minishell *mini, s_tree *tree)
{
	int		i;
	char	*expansion;

	if (tree->type == WORD)
	{
		i = -1;
		while (tree->args[++i])
		{
			if (should_expand(tree->args[i]))
			{
				expansion = expand_variable(mini, tree->args[i]);
				free(tree->args[i]);
				tree->args[i] = expansion;
			}
		}
	}
	if (tree->left)
		expand_tree(mini, tree->left);
	if (tree->right)
		expand_tree(mini, tree->right);
}

static bool	is_expandable(const char *ptr)
{
	return (*ptr == '$' && *(ptr + 1)
		&& *(ptr + 1) != '\'' && *(ptr + 1) != '"' && *(ptr + 1) != ' ');
}

static void	handle_variable(s_minishell *mini, const char **ptr, char **res_ptr)
{
	char	var_name[256];
	char	*value;

	get_variable_name(ptr, var_name);
	value = find_variable(mini, var_name);
	if (ft_strcmp(var_name, "?") == 0)
	{
		append_value_to_result(res_ptr, value);
		free(value);
	}	
	else
		append_value_to_result(res_ptr, value);
}

static void	handle_plain_char(const char **ptr, char **res_ptr)
{
	**res_ptr = **ptr;
	(*res_ptr)++;
	(*ptr)++;
}

char	*expand_variable(s_minishell *mini, const char *arg)
{
	char		*result;
	char		*res_ptr;
	const char	*ptr;

	result = safe_malloc(1024);
	ptr = arg;
	res_ptr = result;
	while (*ptr)
	{
		if (is_expandable(ptr))
			handle_variable(mini, &ptr, &res_ptr);
		else
			handle_plain_char(&ptr, &res_ptr);
	}
	*res_ptr = '\0';
	return (result);
}
