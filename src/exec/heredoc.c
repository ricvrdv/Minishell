/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:31 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:43:27 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc(t_tree *node, t_minishell *mini)
{
	int			fd;
	const char	*delim;
	char		*temp_file;
	bool		quoted;

	delim = node->right->args[0];
	quoted = has_any_quotes(delim);
	if (quoted)
		remove_quotes((char *)delim);
	temp_file = node->right->hd_file;
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	node->right->hd_file = temp_file;
	if(quoted)
		read_heredoc(fd, delim);
	else
		read_heredoc_expand(fd, delim, mini);
	close(fd);
	return (0);
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
			ft_putstr_fd(HEREDOC_EOF_WARNING, 2);
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

int	execute_heredoc(t_tree *tree, t_minishell *mini)
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
