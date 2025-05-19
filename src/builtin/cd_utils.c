/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:29 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:52:04 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_oldpwd(t_env *env);
static char	*get_home_dir(t_env *env);
static char	*expand_tilde_path(t_env *env, const char *path);

char	*get_target_dir(t_minishell *mini, char *arg)
{
	char	*dir;
	char	*expanded;

	if (arg && ft_strcmp(arg, "-") == 0)
		dir = get_oldpwd(mini->env);
	else if (!arg || ft_strcmp(arg, "~") == 0)
		dir = get_home_dir(mini->env);
	else
	{
		if (ft_strcmp(arg, "") == 0)
			return (NULL);
		dir = ft_strdup(arg);
	}
	if (!dir)
		return (NULL);
	if (dir[0] == '~' && dir[1] == '/')
	{
		expanded = expand_tilde_path(mini->env, dir);
		free(dir);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
	return (dir);
}

static char	*get_oldpwd(t_env *env)
{
	t_env	*oldpwd;

	oldpwd = find_env_var(env, "OLDPWD");
	if (!oldpwd || !oldpwd->value || oldpwd->value[0] == '\0')
	{
		ft_putstr_fd("Minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	printf("%s\n", oldpwd->value);
	return (ft_strdup(oldpwd->value));
}

static char	*get_home_dir(t_env *env)
{
	t_env	*home;

	home = find_env_var(env, "HOME");
	if (!home || !home->value)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (ft_strdup(home->value));
}

static char	*expand_tilde_path(t_env *env, const char *path)
{
	t_env	*home;
	char	*expanded;

	if (ft_strncmp(path, "~/", 2) != 0)
		return (NULL);
	home = find_env_var(env, "HOME");
	if (!home || !home->value)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	expanded = ft_strjoin(home->value, path + 1);
	if (!expanded)
		perror("cd: failed to expand tilde path");
	return (expanded);
}
