/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:21 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/09 10:05:43 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_path_variable(s_minishell *mini, s_tree *node)
{
	s_env	*env;

	env = mini->env;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
			return (env->value + 5);
		env = env->next;
	}
	ft_putstr_fd("Command not Found\n", 2);
	clear_tree(&node);
	ft_exit_child(mini, NULL);
	close_fds();
	exit_code(127, 1, 1);
	return (NULL);
}

char	*find_cmd_path(const char *cmd, const char *path)
{
	char	**dir;
	char	*full_path;
	char	*half_path;
	int		i;

	if (ft_strchr(cmd, '/')) // check if there's any '/' in the command
	{
		check_cmd_access(cmd);
		return (ft_strdup(cmd));
	}
	i = 0;
	dir = ft_split(path, ':');
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
	free_split(dir);
	return (NULL);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
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

int	execute_builtin(s_tree *node, s_minishell *mini)
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