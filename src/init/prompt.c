/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:56:27 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 11:09:02 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_sig(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit_code(130, 1, 0);
	}
}

static void	ft_start_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ft_handle_sig;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	start_prompt(t_minishell **mini)
{
	char	*line;
	t_token	*tokens;
	t_tree	*tree;
	int		status;

	(void)mini;
	while (1)
	{
		ft_start_sig();
		line = readline(BLUE "Minishell$ " RESET);
		if (line == NULL)
			break ;
		if (check_str(&line))
			continue ;
		add_history(line);
		tokens = make_token(line, &tokens);
		if (tokens)
		{
			tree = parse_token(&tokens);
			prep_tree(tree, *mini, &status);
			clear_tree(&tree);
			tokens = NULL;
		}
		
	}
}
