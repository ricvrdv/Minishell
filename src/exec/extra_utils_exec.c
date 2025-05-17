/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: applecore <applecore@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:55:22 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/15 16:53:29 by applecore        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	invalid_cmd(s_minishell *mini, s_tree *node)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fds();
	ft_exit_child(mini, NULL);
	exit_code(127, 1, 1);
}

void	invalid_path(s_minishell *mini, s_tree *node)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fds();
	ft_exit_child(mini, NULL);
	exit_code(127, 1, 1);
}

void	execve_fail(s_minishell *mini)
{
	ft_putstr_fd(" Is a directory\n", 2);
	close_fds();
	ft_exit_child(mini, NULL);
	exit_code(126, 1, 1);
}
