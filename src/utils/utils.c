/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 23:38:58 by joaorema         ###   ########.fr       */
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

	result = safe_malloc(1024);
	res_ptr = result;
	ptr = str + 2;
	while (*ptr && *ptr != '"')
		*res_ptr++ = *ptr++;
	if (*ptr == '"')
		ptr++;
	*res_ptr = '\0';
	return (result);
}

bool	is_edge_case(const char *str)
{
	return (str[0] == '$' && str[1] == '"');
}
