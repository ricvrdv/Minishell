/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:55:22 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:41:54 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	invalid_cmd(t_minishell *mini)
{
	ft_putstr_fd(mini->root->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fds();
	ft_exit_child(mini, NULL);
	exit_code(127, 1, 1);
}

void	invalid_path(t_minishell *mini)
{
	ft_putstr_fd(mini->root->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	close_fds();
	ft_exit_child(mini, NULL);
	exit_code(127, 1, 1);
}

void	execve_fail(t_minishell *mini)
{
	ft_putstr_fd(mini->root->args[0], 2);
	ft_putstr_fd(" Is a directory\n", 2);
	close_fds();
	ft_exit_child(mini, NULL);
	exit_code(126, 1, 1);
}
