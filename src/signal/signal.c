/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:28 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/05 16:05:52 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	child_ctrl_c(int sig_num)
{
	if (sig_num == 2)
		g_sig = 130;
	else
	{
		ft_putstr_fd("Quit", 1);
		g_sig = 131;
	}
	write(1, "\n", 1);
}

void	handle_ctrl_c(int a)
{
	(void)a;
	g_sig = 1;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}