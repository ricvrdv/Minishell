/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:57:50 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/08 13:06:31 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_pipe(s_tree *tree, s_minishell *mini)
{
	int		pipefd[2];
	int		in_fd;
	int		status;
	s_tree	*temp;

	temp = tree;
	in_fd = 0;
	status = 0;
	while (tree->type == PIPE)
	{
		in_fd = create_and_fork_command(tree, mini, in_fd, pipefd, temp);
		tree = tree->right;
	}
	execute_last_command(tree, mini, in_fd, temp);
	wait_for_children(&status);
	return (exit_code(WEXITSTATUS(status), 1, 0));
}

int create_and_fork_command(s_tree *node, s_minishell *mini, int in_fd, int *pipefd, s_tree *start)
{
	pid_t pid;
	
	if (pipe(pipefd) < 0)
	perror("pipe");
	pid = fork();
	if (pid == 0)
	{
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
		clear_tree(&start);
		ft_exit_child(mini, NULL);
		exit(0);
	}
	if (in_fd != 0)
	close(in_fd);
	close(pipefd[1]);
	return (pipefd[0]);
}


int execute_last_command(s_tree *node, s_minishell *mini, int in_fd, s_tree *start)
{
	pid_t pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (in_fd != 0)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		mini->is_child = true;
		execute_node(node, mini, STDIN_FILENO, STDOUT_FILENO);
		clear_tree(&start);
		ft_exit_child(mini, NULL);
		exit(0);
	}
	if (in_fd != 0)
	close(in_fd);
	return 0;
}

void wait_for_children(int *last_status)
{
	int status;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		*last_status = status;
	}
}
