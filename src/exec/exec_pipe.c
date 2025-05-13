/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:57:50 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 18:03:38 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_pipe(s_tree *tree, s_minishell *mini)
{
	int		in_fd;
	int		status;

	in_fd = 0;
	status = 0;
	while (tree->type == PIPE)
	{
		in_fd = create_and_fork_command(tree, mini, in_fd);
		tree = tree->right;
	}
	//wait_for_children(&status);
	execute_last_command(tree, mini, in_fd);
	wait_for_children(&status);
	return (exit_code(WEXITSTATUS(status), 1, 0));
}

int	create_and_fork_command(s_tree *node, s_minishell *mini, int in_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int status;

	pid = init_pipe_and_fork(pipefd);
	if (pid == 0)
	{
		ft_sig_child();
		if (in_fd != 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		mini->is_child = true;
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_node(node->left, mini, STDIN_FILENO, STDOUT_FILENO);
		ft_exit_child(mini, NULL);
		if (exit_code(0, 0, 0) != 0)
			exit_code(exit_code(0, 0, 0), 1, 1);
		exit(0);
	}
	if (in_fd != 0)
		close(in_fd);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	execute_last_command(s_tree *node, s_minishell *mini, int in_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_sig_child();
		if (in_fd != 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		mini->is_child = true;
		execute_node(node, mini, STDIN_FILENO, STDOUT_FILENO);
		ft_exit_child(mini, NULL);
		if (exit_code(0, 0, 0) != 0)
			exit_code(exit_code(0, 0, 0), 1, 1);
		exit(0);
	}
	if (in_fd != 0)
		close(in_fd);
	return (0);
}

void	wait_for_children(int *last_status)
{
	int	status;
	int sig;

	ft_sig_mute();
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*last_status = status;
		if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				ft_putstr_fd("\n", 1);
				exit_code(130, 1, 0);                  // 130 = interrupted by SIGI
				return ;
			}
			else if (sig == SIGQUIT)
			{
				ft_putstr_fd("Quit (core dumped)\n", 1);
				exit_code(131, 1, 0);                  // 130 = interrupted by SIGI
				return ;
			}
		}
	}
	ft_sig_restore();
}

pid_t	init_pipe_and_fork(int *pipefd)
{
	pid_t	pid;

	if (pipe(pipefd) < 0)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("fork");
	return (pid);
}
