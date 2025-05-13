/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:27:05 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 12:28:02 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_quotes_2(const char *str)
{
	char	type;

	type = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (type == *str)
				type = 0;
			else if (!type)
				type = *str;
		}
		str++;
	}
	return (type != 0);
}

char	*s_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

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
