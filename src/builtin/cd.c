/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjesus-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:39:05 by rjesus-d          #+#    #+#             */
/*   Updated: 2025/05/07 12:42:09 by rjesus-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_cd_args(s_tree *node);
static int	handle_chdir_failure(const char *dir);
static int	update_pwd_vars(s_minishell *mini, char *oldpwd, char *dir);
static char	*resolve_new_pwd(const char *dir);

int	mini_cd(s_minishell *mini, s_tree *node)
{
	char	oldpwd[PATH_MAX];
	char	*dir;
	int		status;

	status = check_cd_args(node);
	if (status != 0)
		return (status);
	if (!mini->cur_dir
		|| ft_strlcpy(oldpwd, mini->cur_dir, sizeof(oldpwd)) >= sizeof(oldpwd))
	{
		ft_putstr_fd("cd: current directory not set\n", STDERR_FILENO);
		return (exit_code(1, 1, 0));
	}
	dir = get_target_dir(mini, node->args[1]);
	if (!dir || chdir(dir) != 0)
		status = handle_chdir_failure(dir);
	else if (!update_pwd_vars(mini, oldpwd, dir))
		status = 1;
	free(dir);
	sync_env_array(mini);
	return (exit_code(status, 1, 0));
}

static int	check_cd_args(s_tree *node)
{
	if (node->argcount > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		return (exit_code(1, 1, 0));
	}
	return (0);
}

static int	handle_chdir_failure(const char *dir)
{
	if (dir && ft_strcmp(dir, "-") == 0)
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	else
		perror("cd");
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

static int	update_pwd_vars(s_minishell *mini, char *oldpwd, char *dir)
{
	char	*new_pwd;

	new_pwd = resolve_new_pwd(dir);
	if (!new_pwd)
		return (0);
	update_env_var(&mini->env, "OLDPWD", oldpwd);
	update_env_var(&mini->env, "PWD", new_pwd);
	free(mini->cur_dir);
	mini->cur_dir = new_pwd;
	return (1);
}

/*int    mini_cd(s_minishell *mini, s_tree *node)
{
    char    oldpwd[PATH_MAX];
    char    *dir;
    int     status;
    
    status = 0;
    if (node->argcount > 2)
    {
        ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
        return (exit_code(1, 1, 0));
    }
    if (!mini->cur_dir
        || ft_strlcpy(oldpwd, mini->cur_dir, sizeof(oldpwd)) >= sizeof(oldpwd))
    {
        ft_putstr_fd("cd: current directory not set\n", STDERR_FILENO);
        return (exit_code(1, 1, 0));
    }
    dir = get_target_dir(mini, node->args[1]);
    if (!dir || chdir(dir) != 0)
    {
        if (dir && ft_strcmp(dir, "-") == 0)
            ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
        else
            perror("cd");
        status = 1;
    }
    else if (!update_pwd_vars(mini, oldpwd, dir))
        status = 1;
    free(dir);
    sync_env_array(mini);
    return (exit_code(status, 1, 0));
}

static int  update_pwd_vars(s_minishell *mini, char *oldpwd, char *dir)
{
    char    cwd[PATH_MAX];
    char    *new_pwd;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        if (dir[0] == '/')
        {
            new_pwd = ft_strdup(dir);
            if (!new_pwd)
                return (0);
        }
        else
        {
            perror("cd: could not get current directory");
            return (0);
        }
    }
    else
    {
        new_pwd = ft_strdup(cwd);
        if (!new_pwd)
            return (0);
    }
    update_env_var(&mini->env, "OLDPWD", oldpwd);
    update_env_var(&mini->env, "PWD", new_pwd);
    free(mini->cur_dir);
    mini->cur_dir = new_pwd;
    return (1);
}*/
