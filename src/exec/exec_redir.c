#include "../../inc/minishell.h"

static int	exec_redirect_l(s_tree *tree, s_minishell *mini, int out_fd)
{
	int	fd;
	int	status;

	fd = handle_redirect_l(tree);
	if (fd == -1)
		return (report_error(127));
	status = 0;
	if (tree->left)
		status = execute_node(tree->left, mini, fd, out_fd);
	close(fd);
	return (status);
}

static int	exec_redirect_r(s_tree *tree, s_minishell *mini, int in_fd)
{
	int	fd;
	int	status;

	fd = handle_redirect_r(tree);
	if (fd == -1)
		return (report_error(127));
	status = 0;
	if (tree->left)
		status = execute_node(tree->left, mini, in_fd, fd);
	close(fd);
	return (status);
}

static int	exec_heredoc(s_tree *tree, s_minishell *mini, int out_fd)
{
	int	fd;
	int	status;

	fd = handle_heredoc(tree);
	if (fd == -1)
		return (report_error(127));
	status = 0;
	if (tree->left)
		status = execute_node(tree->left, mini, fd, out_fd);
	close(fd);
	return (status);
}

static int	exec_append(s_tree *tree, s_minishell *mini, int in_fd)
{
	int	fd;
	int	status;

	fd = handle_append(tree);
	if (fd == -1)
		return (report_error(127));
	status = execute_node(tree->left, mini, in_fd, fd);
	close(fd);
	return (status);
}

int	execute_redirect(s_tree *tree, s_minishell *mini, int in_fd, int out_fd)
{
	int	status;

	status = 0;
	if (tree->type == REDIRECT_L)
		status = exec_redirect_l(tree, mini, out_fd);
	else if (tree->type == REDIRECT_R)
		status = exec_redirect_r(tree, mini, in_fd);
	else if (tree->type == HEREDOC)
		status = exec_heredoc(tree, mini, out_fd);
	else if (tree->type == APPEND)
		status = exec_append(tree, mini, in_fd);
	return (status);
}
