/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/22 11:41:05 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_exit(char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(1);
}

void	ft_sig_mute(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

char	*deal_edge_case(const char *str)
{
	const char	*ptr;
	char		*result;
	char		*res_ptr;
	char		quote;

	ptr = str;
	result = safe_malloc(1024);
	res_ptr = result;
	while (*ptr)
	{
		if (*ptr == '$' && (ptr[1] == '"' || ptr[1] == '\''))
		{
			quote = ptr[1];
			ptr += 2;
			while (*ptr && *ptr != quote)
				*res_ptr++ = *ptr++;
			if (*ptr == quote)
				ptr++;
		}
		else
			*res_ptr++ = *ptr++;
	}
	*res_ptr = '\0';
	return (result);
}

bool	is_edge_case(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			return (true);
		i++;
	}
	return (false);
}
