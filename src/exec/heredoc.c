/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:31 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/02 11:44:01 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_heredoc(s_tree *node)
{
	int			fd;
	const char	*delimeter;
	char		*temp_file;
	static int 		index;
	

	temp_file = generate_file(index++);
	if(!temp_file)
		return 1;
	fd = open (temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(temp_file);
		return (-1);
	}
	delimeter = node->right->args[0];
	node->right->hd_file = temp_file;
	read_heredoc(fd, delimeter);
	close(fd);
	return (open(temp_file, O_RDONLY));
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
			break ;
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
		fd = handle_heredoc(tree);
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
	ft_strcat(filename, base);
	ft_strcat(filename, num);
	ft_strcat(filename, ".txt");
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

