/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:52:12 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 10:59:19 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_expandable(const char *ptr)
{
	return (*ptr == '$' && *(ptr + 1)
		&& !(*(ptr + 1) == '\'' || *(ptr + 1) == '"' || *(ptr + 1) == ' '));
}

void	expand_tree(t_minishell *mini, t_tree *tree)
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
				if (found_sign(tree->args[i]))
				{
					expansion = expand_variable(mini, tree->args[i]);
					free(tree->args[i]);
					tree->args[i] = expansion;
				}
			}
		}
	}
	if (tree->left)
		expand_tree(mini, tree->left);
	if (tree->right)
		expand_tree(mini, tree->right);
}

static void handle_variable(t_minishell *mini, const char **ptr, char **res_ptr)
{
    char var_name[256];
    char *value;
    
    if (ft_isdigit(*(*ptr + 1)) && *(*ptr + 1) != '0')
	{
        (*ptr)++;
		(*ptr)++;
        return ;
    }
    get_variable_name(ptr, var_name);
    value = find_variable(mini, var_name);
	if (value)
	{
		append_value_to_result(res_ptr, value);
		if (ft_strcmp(var_name, "?") == 0 || ft_strcmp(var_name, "0") == 0)
			free(value);
	}
}

static void	handle_plain_char(const char **ptr, char **res_ptr)
{
	**res_ptr = **ptr;
	(*res_ptr)++;
	(*ptr)++;
}

char	*expand_variable(t_minishell *mini, const char *arg)
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
