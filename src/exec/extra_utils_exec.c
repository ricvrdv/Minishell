/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:55:22 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/08 12:55:33 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	invalid_cmd(s_tree *node, s_minishell *mini)
{
	ft_putstr_fd(" command not found\n", 2);
	close(4);
	close(3);
	clear_tree(&node);
	ft_exit_child(mini, NULL);
	exit(127);
}

void invalid_path(s_tree *node, s_minishell *mini)
{
	ft_putstr_fd(" command not found\n", 2);
	close(4);
	close(3);
	clear_tree(&node);
	ft_exit_child(mini, NULL);
	exit_code(127, 1, 1);
}

void execve_fail(s_tree *node, s_minishell *mini)
{
	ft_putstr_fd(" Is a directory\n", 2);
	close(3);
	close(4);
	clear_tree(&node);
	ft_exit_child(mini, NULL);
	exit_code(126, 1, 1);
}