/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:59:51 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 11:00:02 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirect_l(s_tree *tree)
{
	int	fd;

	fd = open(tree->right->args[0], O_RDONLY);
	if (fd == -1)
	{
		perror("Input redirection failed");
		return (-1);
	}
	return (fd);
}

int	handle_redirect_r(s_tree *tree)
{
	int	fd;

	fd = open(tree->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		return (-1);
	}
	return (fd);
}

int	handle_append(s_tree *tree)
{
	int	fd;

	fd = open(tree->right->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		return (-1);
	}
	return (fd);
}
