/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:31 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/12 23:06:07 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	process_heredoc_child(int fd, const char *delim, bool quoted, s_minishell *mini)
{
	if (quoted)
		read_heredoc(fd, delim);
	else
		read_heredoc_expand(fd, delim, mini);
	close_heredoc(mini, fd);
	exit(0);
}

int	handle_heredoc(s_tree *node, s_minishell *mini)
{
	int			fd;
	const char	*delim;
	char		*temp_file;
	int			pid;
	int			status;
	bool		quoted;

	status = 0;
	delim = node->right->args[0];
	quoted = has_any_quotes(delim);
	if (quoted)
		remove_quotes((char *)delim);
	temp_file = generate_file(static_index());
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	node->right->hd_file = temp_file;
	pid = fork();
	if (pid == 0)
		process_heredoc_child(fd, delim, quoted, mini);
	else if (handle_heredoc_wait(pid, &status, node))
		return (-1);
	close(fd);
	return open(temp_file, O_RDONLY);
}


void	read_heredoc(int fd, const char *delimiter)
{
	char	*line;
	size_t	len;

	len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
			break ;
		}
		if (ft_strncmp(line, delimiter, len) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

int	execute_heredoc(s_tree *tree, s_minishell *mini)
{
	int	fd;

	if (tree->type == HEREDOC)
	{
		fd = handle_heredoc(tree, mini);
		if (fd == -1)
		{
			report_error(127);
			return (-1);
		}
		mini->heredoc_fd = fd;
		return (0);
	}
	if (execute_heredoc(tree->left, mini) == 0)
		return (0);
	return (execute_heredoc(tree->right, mini));
}




