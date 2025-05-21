/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:31 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 10:15:27 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	read_heredoc(int fd, const char *delimiter)
{
	char	*line;

	remove_quotes((char *)delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd(HEREDOC_EOF_WARNING, 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

int	handle_heredocs(t_tree *tree, t_minishell *mini)
{
	int	fd;

	if (!tree)
		return (0);
	if (tree->type == HEREDOC)
	{
		fd = open(tree->right->hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (-5);
		if (has_any_quotes(tree->right->args[0]))
			read_heredoc(fd, tree->right->args[0]);
		else
			read_heredoc_expand(fd, tree->right->args[0], mini);
		close(fd);
	}
	if (handle_heredocs(tree->left, mini) == -5)
		return (-5);
	if (handle_heredocs(tree->right, mini) == -5)
		return (-5);
	return (0);
}

void	handle_heredoc_fork(pid_t pid, t_tree *tree, t_minishell *mini)
{
	int	status;
	int	ret;

	ft_sig_mute();
	if (pid == 0)
	{
		clear_mini(mini, 0);
		ft_sig_child_heredoc();
		ret = handle_heredocs(tree, mini);
		ft_exit_child(mini, NULL);
		if (ret == -5)
			exit(130);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) != 0))
		tree->bad_herdoc = 1;
	ft_sig_restore();
}

void	assign_heredoc_filenames(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == HEREDOC && tree->right)
	{
		if (!tree->right->hd_file)
			tree->right->hd_file = generate_file(static_index());
	}
	assign_heredoc_filenames(tree->left);
	assign_heredoc_filenames(tree->right);
}
