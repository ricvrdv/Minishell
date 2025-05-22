/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:21 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/22 13:03:15 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path_variable(t_minishell *mini)
{
	t_env	*env;

	env = mini->env;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*search_path_dirs(char **dir, const char *cmd)
{
	char	*half_path;
	char	*full_path;
	int		i;

	i = 0;
	while (dir[i])
	{
		half_path = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(half_path, cmd);
		free(half_path);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(const char *cmd, const char *path, t_minishell *mini)
{
	char	**dir;
	char	*found_path;

	if (ft_strchr(cmd, '/'))
	{
		check_cmd_access(cmd, mini);
		return (ft_strdup(cmd));
	}
	if (!path)
	{
		if (!check_cmd_access(cmd, mini))
			return (ft_strdup(cmd));
	}
	if (ft_strcmp(cmd, ".") == 0 || ft_strcmp(cmd, "..") == 0)
		return (NULL);
	dir = ft_split(path, ':');
	found_path = search_path_dirs(dir, cmd);
	free_split(dir);
	return (found_path);
}

int	redirect_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 for stdin failed!");
			return (-1);
		}
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 for stdout failed!");
			return (-1);
		}
		close(out_fd);
	}
	return (0);
}

int	execute_builtin(t_tree *node, t_minishell *mini)
{
	int	status;

	status = 0;
	if (ft_strcmp(node->args[0], "cd") == 0)
		status = mini_cd(mini, node);
	else if (ft_strcmp(node->args[0], "echo") == 0)
		status = mini_echo(node);
	else if (ft_strcmp(node->args[0], "pwd") == 0)
		status = mini_pwd(mini);
	else if (ft_strcmp(node->args[0], "export") == 0)
		status = mini_export(mini, node);
	else if (ft_strcmp(node->args[0], "unset") == 0)
		status = mini_unset(mini, node);
	else if (ft_strcmp(node->args[0], "env") == 0)
		status = mini_env(mini, node);
	else if (ft_strcmp(node->args[0], "exit") == 0)
		status = mini_exit(mini, node);
	else
		status = 127;
	return (exit_code(status, 1, 0));
}
