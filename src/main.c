#include "../inc/minishell.h"

int	g_sig = 0;

int	main(int ac, char *av[], char **envp)
{
	s_minishell	*mini;

	(void)av;
	exit_code(0, 1, 0);
	setup_signal_handling();
	mini = safe_malloc(sizeof(s_minishell));
	init_struct(mini);
	if (ac == 1 && get_env(mini, envp))
	{
		start_prompt(&mini);
		ft_exit(mini, "LEAVING");
	}
	ft_exit(mini, "No arguments plz");
	return (0);
}