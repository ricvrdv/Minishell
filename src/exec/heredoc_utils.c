/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:59:46 by joaorema          #+#    #+#             */
/*   Updated: 2025/05/13 11:39:24 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	ft_strlcat(dest, src, dest_len + ft_strlen(src) + 1);
	return (dest);
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
	if ((delim[0] == '\'' && delim[len - 1] == '\'')
		|| (delim[0] == '\"' && delim[len - 1] == '\"'))
		return (true);
	return (false);
}

bool	has_any_quotes(const char *delim)
{
	while (*delim)
	{
		if (*delim == '\'' || *delim == '\"')
			return (true);
		delim++;
	}
	return (false);
}

int	handle_heredoc_wait(int pid, s_tree *node)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		node->bad_herdoc = 1;
		return (-1);
	}
	return (0);
}
