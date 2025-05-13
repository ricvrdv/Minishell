/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 16:32:53 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_exit(char *error)
{
	printf(RED"%s\n"RESET, error);
	exit(1);
}

char	*get_dir(void)
{
	char	*currentdir;

	currentdir = getcwd(NULL, 1024);
	return (currentdir);
}

int	found_sign(const char *str)
{
	int		i;
	char	next;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			next = str[i + 1];
			if (ft_isalpha(next) || ft_isdigit(next)
				|| next == '_' || next == '?')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	handle_heredocs(s_tree *tree, s_minishell *mini)
{
	int	fd;
	int ret;

	if (!tree)
		return (1);
	if (tree->type == HEREDOC)
	{
		fd = handle_heredoc(tree, mini);
		if(fd == -5)
			return(-5);
		close(fd);
	}
	if (tree->left)
	{
		ret = handle_heredocs(tree->left, mini);
		if(ret == -5)
			return(-5);
	}
	if (tree->right)
	{
		ret = handle_heredocs(tree->right, mini);
		if(ret == -5)
			return(-5);
	}
	return (0);
}

void	ft_exit_child(s_minishell *mini, char *error)
{
	if (mini->created)
		free_mini_struct(mini);
	if (error)
		printf(RED "%s\n" RESET, error);
	clear_history();
	free(mini);
}
