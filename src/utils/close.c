/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:51:53 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 18:14:00 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_heredoc(t_minishell *mini, int fd)
{
	ft_exit_child(mini, NULL);
	close(fd);
	close_fds();
}

void	print_heredoc(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	free(str);
}

void	close_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 100)
	{
		close(fd);
		fd++;
	}
}

void	ft_exit_child(t_minishell *mini, char *error)
{
	if (mini->created)
		free_mini_struct(mini);
	if (error)
		printf(RED "%s\n" RESET, error);
	rl_clear_history();
	free(mini);
}

void	close_pipefd(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}
