/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:17:20 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:51 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char *av[], char **envp)
{
	t_minishell	*mini;

	(void)av;
	exit_code(0, 1, 0);
	mini = safe_malloc(sizeof(t_minishell));
	init_struct(mini);
	if (ac == 1 && get_env(mini, envp))
	{
		start_prompt(&mini);
		ft_putstr_fd("exit\n", 2);
		free_struct(mini);
		free(mini);
		exit(0);
	}
	ft_exit(mini, "No arguments plz");
	return (0);
}
