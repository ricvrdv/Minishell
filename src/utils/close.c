/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:51:53 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 12:51:54 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/minishell.h"

void	close_heredoc(s_minishell *mini, int fd)
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
	close(3);
	close(4);
	close(5);
	close(6);
	close(7);
	close(8);
	close(9);
}
