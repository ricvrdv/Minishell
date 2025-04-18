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
			if(should_expand(tree->args[i]))							//if double or no quotes expand 
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

char	*expand_variable(s_minishell *mini, const char *arg)
{
	char		*result;
	char		var_name[256];
	const char	*ptr;
	char		*res_ptr;
	char		*value;

	result = safe_malloc(1024);
	ptr = arg;
	res_ptr = result;
	while (*ptr)
	{
		if (*ptr == '$' && *(ptr + 1) != '\0' && *(ptr + 1) != 39 && *(ptr + 1) != 34)
		{
			get_variable_name(&ptr, var_name);
			value = find_variable(mini, var_name);
			if (ft_strcmp(var_name, "?") == 0)
            {
                append_value_to_result(&res_ptr, value);
                free(value);
            }
			else
				append_value_to_result(&res_ptr, value);
		}
		else
			*res_ptr++ = *ptr++;
	}
	*res_ptr = '\0';
	return (result);
}

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
	return (false);											//dont have single but can have double
}

bool	should_expand(const char *str)
{
	if (!str)
		return (false);
	if (enclosed_single_quotes(str))						// if str inside single quotes return false dont expand
		return (false); 
	return (true); 											//any other case expand $user "$user"	
}