/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/12 23:03:07 by joaorema         ###   ########.fr       */
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

int handle_heredocs(s_tree *tree, s_minishell *mini)
{
	int fd;
	
	if(!tree)
		return 1;
	if(tree->type == HEREDOC)
	{
		fd = handle_heredoc(tree, mini);
		close(fd);	
	}
	if(tree->left)
		handle_heredocs(tree->left, mini);
	if(tree->right)
		handle_heredocs(tree->right, mini);
	return 0;
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

void close_heredoc(s_minishell *mini, int fd)
{
	ft_exit_child(mini, NULL);
	close(fd);
	close_fds();
}

void print_heredoc(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	free(str);
}

void	close_fds()
{
	close(3);
	close(4);
	close(5);
	close(6);
	close(7);
	close(8);
	close(9);
}