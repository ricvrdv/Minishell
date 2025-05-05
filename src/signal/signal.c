#include "../../inc/minishell.h"

/*
void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_handling(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = handle_sigint;
	sigaction(SIGINT, &action, NULL);
}
*/

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
		signal(SIGINT, sig_child_handler);
		signal(SIGQUIT, sig_child_handler);
	}
	if (type == DEFAULT_)
	{
		sig_default();
	}
}

static void	sig_heredoc_parent_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit_code(130, 1, 0);
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
	signal(SIGINT, sig_heredoc_parent_handler);
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