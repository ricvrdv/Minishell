/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:28 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/20 13:59:06 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"  

t_minishell *clear_mini(t_minishell *mini, int flag)
{
	static t_minishell *ptr;
	
	if(flag)
		return(ptr);
	ptr = mini;
	return (ptr);
}

void	ft_sig_restore(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_sig_child_heredoc(void)
{
	struct sigaction sa;

	sa.sa_handler = ft_sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	signal(SIGQUIT, SIG_IGN); // still fine to use signal() for this
}

void	ft_sig_mute(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sigint_handler(int sig)
{
	t_minishell	*mini = clear_mini(NULL, 1);

	(void)sig;
	
	write(STDOUT_FILENO, "\n", 1);
	ft_exit_child(mini, NULL);
	close_fds();
	exit_code(130, 1, 1);
}
