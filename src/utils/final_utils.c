/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:46:17 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/20 15:24:56 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_sigint(void)
{
	ft_putstr_fd("\n", 1);
	exit_code(130, 1, 0);
}

void	print_sigquit(void)
{
	ft_putstr_fd("Quit (core dumped)\n", 1);
	exit_code(131, 1, 0);
}

void	check_builtin(int *status, t_tree *tree, t_minishell *mini) //
{
	*status = execute_builtin(tree, mini);
	exit_code(*status, 1, 0);
}