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

void	handle_exit_cleanup(s_minishell *mini, s_tree *node, int code)
{
	free_struct(mini);
	free(mini);
	clear_history();
	clear_tree(&node);
	close(4);
	close(3);
	close(5);
	close(6);
	exit_code(code, 1, 1);
}
