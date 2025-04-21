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
	return (1);
}
