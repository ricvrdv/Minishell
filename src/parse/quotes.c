/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:59 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 10:56:00 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quote_counter(char c, int *s_counter, int *d_counter)
{
	if (c == '\"')
		(*d_counter)++;
	else if (c == '\'')
		(*s_counter)++;
}

void	update_quotes(char c, int *inside, char *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*inside && c == *quote)
			*inside = 0;
		else if (!*inside)
		{
			*inside = 1;
			*quote = c;
		}
	}
}

int	check_str(char **line)
{
	if (*line[0] == '\0' || (ft_strncmp(*line, "\n", 2) == 0)
		|| is_space(*line))
	{
		free(*line);
		return (1);
	}
	return (0);
}
