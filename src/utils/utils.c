/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:38 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/16 15:13:39 by Jpedro-c         ###   ########.fr       */
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
int handle_heredocs(s_tree *tree, s_minishell *mini)
{
    int fd;
    if (!tree)
        return 0;
    if (tree->type == HEREDOC)
    {
        fd = open(tree->right->hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
            return -5;
        if (has_any_quotes(tree->right->args[0]))
            read_heredoc(fd, tree->right->args[0]);
        else
            read_heredoc_expand(fd, tree->right->args[0], mini);
        close(fd);
    }
    if (handle_heredocs(tree->left, mini) == -5)
        return -5;
    if (handle_heredocs(tree->right, mini) == -5)
        return -5;
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
