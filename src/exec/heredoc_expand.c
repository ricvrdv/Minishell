/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 23:05:41 by joaorema          #+#    #+#             */
/*   Updated: 2025/05/12 23:06:05 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
				print_heredoc(expansion, fd);
		}
		else
		{
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		free(line);
	}
}

int		static_index(void)
{
	static int i;
	return (i++);
}
