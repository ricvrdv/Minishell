/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:19:32 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:43:25 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_cd_args(t_tree *node);
static int	handle_chdir_failure(const char *dir, t_minishell *mini);
static int	update_pwd_vars(t_minishell *mini, char *oldpwd, char *dir);
static char	*resolve_new_pwd(const char *dir);

int	mini_cd(t_minishell *mini, t_tree *node)
{
	char	oldpwd[PATH_MAX];
	char	*dir;
	int		status;

	status = check_cd_args(node);
	if (status != 0)
		return (status);
	else if (!mini->cur_dir
		|| ft_strlcpy(oldpwd, mini->cur_dir, sizeof(oldpwd)) >= sizeof(oldpwd))
	{
		ft_putstr_fd("cd: current directory not set\n", STDERR_FILENO);
		return (exit_code(1, 1, 0));
	}
	dir = get_target_dir(mini, node->args[1]);
	if (!dir || chdir(dir) != 0)
	{
		if (!dir)
			return (exit_code(0, 1, 0));
		status = handle_chdir_failure(dir, mini);
	}
	else if (!update_pwd_vars(mini, oldpwd, dir))
		status = 1;
	free(dir);
	sync_env_array(mini);
	return (exit_code(status, 1, 0));
}

static int	check_cd_args(t_tree *node)
{
	if (node->argcount > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		return (exit_code(1, 1, 0));
	}
	return (0);
}

static int	handle_chdir_failure(const char *dir, t_minishell *mini)
{
	if (dir && ft_strcmp(dir, "-") == 0)
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	else
    {
        ft_putstr_fd("Minishell: ", 2);
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(mini->root->args[1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        
    }
	return (1);
}

static char	*resolve_new_pwd(const char *dir)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup(cwd));
	if (dir[0] == '/')
		return (ft_strdup(dir));
	perror("cd: could not get current directory");
	return (NULL);
}

static int	update_pwd_vars(t_minishell *mini, char *oldpwd, char *dir)
{
	char	*new_pwd;

	new_pwd = resolve_new_pwd(dir);
	if (!new_pwd)
		return (0);
	update_env_var(&mini->env, "OLDPWD", oldpwd);
	free(mini->cur_dir);
	mini->cur_dir = new_pwd;
	return (1);
}
