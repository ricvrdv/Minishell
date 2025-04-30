/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:56:25 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/30 15:16:57 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_struct(s_minishell *mini)
{
	char	*curdir;

	mini->created = 1;
	curdir = get_dir(mini);
	mini->exit_status = 0;
	mini->cur_dir = curdir;
	mini->heredoc_count = 0;
	mini->heredoc_fd = 0;
	mini->heredoc_index = 0;
	mini->is_child = false;
	mini->env_array = NULL;
	mini->env = NULL;
}

static char	**create_env_array(char **envp)
{
	char	**env_array;
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	while (envp[count])
		count++;
	env_array = malloc((count + 1) * sizeof(char *));
	while (envp[i])
	{
		env_array[i] = ft_strdup(envp[i]);
		if (!env_array[i])
		{
			j = 0;
			while (j < i)
				free(env_array[j++]);
			free(env_array);
			return (NULL);
		}
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}
static void update_shell_level(s_minishell *mini)
{
    s_env   *shlvl_var;
    int     current_level;
    char    *new_level;
	char	*key;
	char	*value;

    shlvl_var = find_env_var(mini->env, "SHLVL");
    if (shlvl_var && shlvl_var->value)
    {
        current_level = ft_atoi(shlvl_var->value);
        if (current_level < 0)
            current_level = 0;
        new_level = ft_itoa(current_level + 1);
        if (!new_level)
            exit(EXIT_FAILURE);
        free(shlvl_var->value);
        shlvl_var->value = new_level;
    }
    else
    {
		key = ft_strdup("SHLVL");
		value = ft_itoa(1);
		if (!key | !value)
		{
			free(key);
			free(value);
			exit(EXIT_FAILURE);
		}
		add_env_node(&mini->env, key, value);
    }
}

int	get_env(s_minishell *mini, char **envp)
{
	char		*sign;
	char		*key;
	char		*value;
	int			i;

	mini->env_array = create_env_array(envp);
	if (!mini->env_array)
		exit(EXIT_FAILURE);
	i = 0;
	while (envp[i])
	{
		sign = ft_strchr(envp[i], '=');
		if (sign)
		{
			key = ft_substr(envp[i], 0, (sign - envp[i]));
			value = ft_strdup(sign + 1);
			if (!key || !value)
				return (0);
			add_env_node(&(mini->env), key, value);
		}
		i++;
	}
	update_shell_level(mini);
	sync_env_array(mini);
	return (1);
}
