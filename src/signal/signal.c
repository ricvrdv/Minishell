#include "../../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signal_handling(void)
{
	struct sigaction	action;

	memset(&action, 0, sizeof(action));
	action.sa_handler = handle_sigint;
	sigaction(SIGINT, &action, NULL);
}
