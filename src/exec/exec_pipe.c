/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:57:50 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/02 12:10:14 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_and_fork(int *pipefd)
{
	int	res;

	res = pipe(pipefd);
	if (res == -1)
		error_exit("Pipe failed!");
	return (0);
}

int		child_process(s_tree *node, s_minishell *mini, int *pipefd, int dir)
{
	int status;

	status = 0;
	if (dir == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	status = execute_node(node->left, mini, 0, 1);
	clear_tree(&node);
	ft_exit(mini, NULL);
	exit(status);
}

int	execute_pipe(s_tree *tree, s_minishell *mini)
{
	int		pipefd[2];
	int		status;
	pid_t	left_pid;
	pid_t 	right_pid;

	left_pid = 0;
	right_pid = 0;
	status = 0;
	pipe_and_fork(pipefd);
	if (tree->left)
	{
		left_pid = fork();
		if (left_pid == 0)
			child_process(tree, mini, pipefd, 0);
	}
	if (tree->right)
	{
		right_pid = fork();
		if (right_pid == 0)
			child_process_right(tree, mini, pipefd, 1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if(left_pid > 0)
		waitpid(left_pid, NULL, 0);
	if(right_pid > 0)
		waitpid(right_pid, &status, 0);
	if (WIFEXITED(status))
		return (exit_code(WEXITSTATUS(status), 1, 0));
	else if (WIFSIGNALED(status))
		return (exit_code(128 + WTERMSIG(status), 1, 0));
	return (exit_code(status, 1, 0));
}

int	check_cmd_access(const char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	else if (access(cmd, F_OK) == 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		exit(126);
	}
	else
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		exit(127);
	}
}

int		child_process_right(s_tree *node, s_minishell *mini, int *pipefd, int dir)
{
	int status;

	status = 0;
	if (dir == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	status = execute_node(node->right, mini, 0, 1);
	clear_tree(&node);
	ft_exit(mini, "teste");
	exit(status);
}