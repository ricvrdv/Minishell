/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:31 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/08 12:44:35 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc(s_tree *node, s_minishell *mini, s_tree *first)
{
	int			fd;
	const char	*delimeter;
	char		*temp_file;
	static int 		index;
	int 			pid;
	int 			status;
	bool 			quoted;
	
	status = 0;
	delimeter = node->right->args[0];
	quoted = has_any_quotes(delimeter);
	if(quoted)
		remove_quotes((char *) delimeter);
	temp_file = generate_file(index++);
	if(!temp_file)
		return 1;
	fd = open (temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(temp_file);
		return (-1);
	}
	node->right->hd_file = temp_file;
	pid = fork();
	if(pid == 0)
	{
		if(quoted)
			read_heredoc(fd, delimeter);
		else
			read_heredoc_expand(fd, delimeter, mini);
		clear_tree(&first);
		ft_exit_child(mini, NULL);
		close(fd);
		close_fds();
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			node->bad_herdoc = 1; // or return -1 if you prefer
			return (-1);
		}
	}
	close(fd);
	fd = open(temp_file, O_RDONLY);
	return (fd);
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

	if (tree == NULL)
		return (-1);
	if (tree->type == HEREDOC)
	{
		fd = handle_heredoc(tree, mini, tree);
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

char	*generate_file(int index)
{
	char	*base;
	char	*num;
	char	*filename;
	int		len;

	base = "/tmp/heredoc_tmp_";
	num = ft_itoa(index);
	if (!num)
		return (NULL);
	len = ft_strlen(base) + ft_strlen(num) + 4;
	filename = safe_malloc(len);
	filename[0] = '\0';
	ft_strlcat(filename, base, len);
	ft_strlcat(filename, num, len);
	ft_strlcat(filename, ".txt", len);
	free(num);
	return filename;
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	ft_strlcat(dest, src, dest_len + ft_strlen(src) + 1);
	return dest;
}

void	quite_heredoc(int a)
{
	(void)a;
	write(1, "\n", 1);
	exit(0);
}

bool	is_quoted(const char *delim)
{
	size_t	len;

	if (!delim)
		return (false);
	len = ft_strlen(delim);
	if (len < 2)
		return (false);
	if ((delim[0] == '\'' && delim[len - 1] == '\'') ||
		(delim[0] == '\"' && delim[len - 1] == '\"'))
		return (true);
	return (false);
}

void read_heredoc_expand(int fd, const char *delimiter, s_minishell *mini)
{
	char	*line;
	char	*expansion;
	size_t	len;

	len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file\n", 2);
			break;
		}
		if (ft_strncmp(line, delimiter, len) == 0 && line[len] == '\0')
		{
			free(line);
			break;
		}
		if (found_sign(line)) // contains $
		{
			expansion = expand_variable(mini, line);
			if (expansion)
			{
				ft_putstr_fd(expansion, fd);
				ft_putstr_fd("\n", fd);
				free(expansion);
			}
		}
		else
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		free(line);
	}
}

bool	has_any_quotes(const char *delim)
{
	while (*delim)
	{
		if (*delim == '\'' || *delim == '\"')
			return true;
		delim++;
	}
	return false;
}

void	close_fds()
{
	close(3);
	close(4);
	close(5);
	close(6);
	close(7);
	close(8);
	close(9);
}
