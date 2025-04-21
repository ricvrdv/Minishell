/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:34 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 15:45:03 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_quotes(char *arg, s_tree *tree)
{
	int	len;

	len = ft_strlen(arg);
	if (len > 1 && arg[0] == '\'' && arg[len - 1] == '\'')
	{
		arg[len - 1] = '\0';
		ft_memmove(arg, arg + 1, len - 1);
	}
	else if (len > 1 && arg[0] == '"' && arg[len - 1] == '"')
	{
		arg[len - 1] = '\0';
		ft_memmove(arg, arg + 1, len - 1);
		tree->d_quoute = 1;
	}
}

void	remove_trailing(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	while (len > 0 && arg[len - 1] == '"')
	{
		arg[len - 1] = '\0';
		len--;
	}
}

void	leading_quotes(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (len > 1 && str[0] == '"' && str[1] == '"')
	{
		ft_memmove(str, str + 2, len - 1);
		str[len - 2] = '\0';
		len -= 2;
	}
}

int	count_quotes(const char *str)
{
	int	counter;
	int	len;
	int	i;

	i = 0;
	counter = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '"')
			counter++;
		i++;
	}
	return (counter);
}

void	clean_args(char **args, int arg_count, s_tree *tree)
{
	int	index;

	index = 0;
	while (index < arg_count)
	{
		remove_quotes(args[index], tree);
		index++;
	}
}
