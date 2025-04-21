/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:57:50 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 10:57:51 by Jpedro-c         ###   ########.fr       */
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

void	child_process(s_tree *node, s_minishell *mini, int *pipefd, int dir)
{
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
	execute_node(node, mini, 0, 1);
	exit(0);
}

int	execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd)
{
	int		pipefd[2];
	int		status;
	int		final_status;
	pid_t	pid;

	pipe_and_fork(pipefd);
	final_status = 0;
	if (tree->left)
	{
		pid = fork();
		if (pid == 0)
			child_process(tree->left, mini, pipefd, 0);
		close(pipefd[1]);
	}
	if (tree->right)
	{
		pid = fork();
		if (pid == 0)
			child_process(tree->right, mini, pipefd, 1);
		close(pipefd[0]);
	}
	while (wait(&status) != -1)
		if (WIFEXITED(status))
			final_status = WEXITSTATUS(status);
	return (exit_code(final_status, 1, 0));
}
