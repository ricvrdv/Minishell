/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:28 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/05 15:01:29 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	sig_parent_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit_code(130, 1, 0);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sig_child_handler(int sig)
{
	if (sig == SIGINT)
	{
	}
	if (sig == SIGQUIT)
	{
	}
	if (sig == SIGPIPE)
		exit_code(141, 1, 0);
}

static void	sig_default(void)
{
	signal(SIGPIPE, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
static void	sig_heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit_code(130, 1, 1);
		exit(130);
	}
}

void	ft_signal(int type)
{
	if (type == PARENT_)
	{
		signal(SIGINT, sig_parent_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (type == CHILD_)
	{
		signal(SIGPIPE, sig_child_handler);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (type == DEFAULT_)
	{
		sig_default();
	}
	if(type == HERE_SIG)
	{
		ft_sig_mute();
		signal(SIGINT, sig_heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}


static void	sig_heredoc_child_handler(int sig)
{
	if (sig == SIGINT)
	{
		close(STDIN_FILENO);
		exit_code(130, 1, 0);
	}
}

void	sig_heredoc_parent(void)
{
	signal(SIGINT, sig_heredoc_handler);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc_child(void)
{
	signal(SIGINT, sig_heredoc_child_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_print_signal(void)
{
	if (exit_code(0, 0, 0) == 130)
		write(1, "\n", 1);
	if (exit_code(0, 0, 0) == 131)
		write(1, "Quit (core dumped)\n", 20);
}

void	ft_sig_mute(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}