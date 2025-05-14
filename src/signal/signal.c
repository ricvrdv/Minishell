/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:28 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/14 15:47:21 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static s_minishell *g_mini = NULL;


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

void 	ft_sig_child_heredoc(s_minishell *mini)
{
	g_mini = mini;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sig_mute(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}


void ft_sigint_handler(int sig) 
{
	(void)sig; // if unused
	if (g_mini)
	{
		close_fds();
		ft_exit_child(g_mini, NULL);
	}
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}