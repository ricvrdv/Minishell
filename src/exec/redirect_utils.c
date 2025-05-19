/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:59:51 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:43:27 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_redirect_l(t_tree *tree)
{
	int		fd;
	char	*file;

	file = remove_quotes_redirect(tree->right->args[0]);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
	{
		perror("Input redirection failed");
		exit_code(1, 1, 0);
		return (-1);
	}
	return (fd);
}

int	handle_redirect_r(t_tree *tree)
{
	int		fd;
	char	*file;
	char	*join;

	join = join_args(tree->right->args);
	file = strip_quotes_and_join(join);
	free(join);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(file);
		perror("Output redirection failed");
		exit_code(1, 1, 0);
		return (-1);
	}
	free(file);
	return (fd);
}

int	handle_append(t_tree *tree)
{
	int	fd;

	fd = open(tree->right->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		exit_code(1, 1, 0);
		return (-1);
	}
	return (fd);
}

char	*remove_quotes_redirect(char *str)
{
	char	*new_str;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
	{
		new_str = ft_substr(str, 1, len - 2);
		return (new_str);
	}
	return (ft_strdup(str));
}

void	setup_cmd(t_tree *node, int in_fd, int out_fd)
{
	redirect_fds(in_fd, out_fd);
	pre_clean_args(node->args, &node->argcount);
	clean_args(node->args, node->argcount);
}
