/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/02 12:06:36 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_exit(char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(1);
}


char	*get_dir()
{
	char	*currentdir;

	currentdir = getcwd(NULL, 1024);
	return (currentdir);
}

int	found_sign(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int handle_heredocs(s_tree *tree)
{
	int fd;
	
	if(!tree)
		return 1;
	if(tree->type == HEREDOC)
	{
		fd = handle_heredoc(tree);
		close(fd);	
	}
	if(tree->left)
		handle_heredocs(tree->left);
	if(tree->right)
		handle_heredocs(tree->right);
	return 0;
}