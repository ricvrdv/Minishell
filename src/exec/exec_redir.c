/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:57:52 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/20 10:35:40 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	exec_redirect_l(t_tree *tree, t_minishell *mini, int out_fd)
{
	int	fd;
	int	status;

	fd = handle_redirect_l(tree);
	if (fd == -1)
		return (report_error(1));
	status = 0;
	if (tree->left)
		status = execute_node(tree->left, mini, fd, out_fd);
	close(fd);
	return (status);
}

static int	exec_redirect_r(t_tree *tree, t_minishell *mini, int in_fd)
{
	int	fd;
	int	status;

	fd = handle_redirect_r(tree);
	if (fd == -1)
		return (report_error(1));
	status = 0;
	if (tree->left)
		status = execute_node(tree->left, mini, in_fd, fd);
	close(fd);
	return (status);
}

static int	setup_heredoc(t_tree *tree, t_minishell *mini, int out_fd)
{
	int	fd;
	int	status;

	status = 0;
	if (!tree->right->bad_herdoc)
	{
		fd = open (tree->right->hd_file, O_RDONLY);
		if (fd == -1)
			return (report_error(1));
		status = 0;
		if (tree->left)
			status = execute_node(tree->left, mini, fd, out_fd);
		close(fd);
		return (status);
	}
	return (status);
}

static int	exec_append(t_tree *tree, t_minishell *mini, int in_fd)
{
	int	fd;
	int	status;

	fd = handle_append(tree);
	if (fd == -1)
		return (report_error(1));
	status = execute_node(tree->left, mini, in_fd, fd);
	close(fd);
	return (status);
}

int	execute_redirect(t_tree *tree, t_minishell *mini, int in_fd, int out_fd)
{
	int	status;

	status = 0;
	if (tree->type == REDIRECT_L)
		status = exec_redirect_l(tree, mini, out_fd);
	else if (tree->type == REDIRECT_R)
		status = exec_redirect_r(tree, mini, in_fd);
	else if (tree->type == HEREDOC)
		status = setup_heredoc(tree, mini, out_fd);
	else if (tree->type == APPEND)
		status = exec_append(tree, mini, in_fd);
	return (status);
}
