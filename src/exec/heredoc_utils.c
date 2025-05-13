/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:59:46 by joaorema          #+#    #+#             */
/*   Updated: 2025/05/13 16:21:39 by Jpedro-c         ###   ########.fr       */
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

int	handle_heredoc_wait(pid_t pid, s_tree *node)
{
	int	status;
	int sig;

	ft_sig_mute();
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			unlink(node->right->hd_file); // delete temp file
			exit_code(130, 1, 0);                  // 130 = interrupted by SIGI
			return (-1);
		}
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(node->right->hd_file);
		g_sig = WEXITSTATUS(status);
		return (1);
	}
	ft_sig_restore();
	return (0); // heredoc completed successfully
}

