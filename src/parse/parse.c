/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:54 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 12:28:57 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	full_check(char *str)
{
	char	*temp;

	temp = ft_strtrim(str, " \t\n\v\f\r");
	if (check_quotes(temp))
		return (handle_error(temp, "Unclosed quote\n"));
	if (check_redirect(temp))
		return (handle_error(temp, "syntax error near unexpected token.\n"));
	if (check_doubles(temp))
		return (handle_error(temp, "Logical operators are not supported.\n"));
	if (check_pipe(temp))
		return (handle_error(temp, "Misplaced operator.\n"));
	free(temp);
	return (0);
}

int	check_doubles(char *str)
{
	int	d_counter;
	int	s_counter;

	d_counter = 0;
	s_counter = 0;
	while (*str)
	{
		quote_counter(*str, &s_counter, &d_counter);
		if (are_counts_odd(d_counter, s_counter)
			&& ((*str == '&' && *(str + 1) == '&')
				|| (*str == '|' && *(str + 1) == '|')))
			return (1);
		str++;
	}
	return (0);
}

int	check_redirect(char *str)
{
	int	s_count;
	int	d_count;

	s_count = 0;
	d_count = 0;
	while (*str)
	{
		quote_counter(*str, &s_count, &d_count);
		if (are_counts_odd(d_count, s_count) && (*str == '<' || *str == '>'))
		{
			if (invalid_operator(&str))
				return (1);
		}
		else
			str++;
	}
	return (0);
}

int	check_pipe(char *str)
{
	int	flag;
	int	s_count;
	int	d_count;

	s_count = 0;
	d_count = 0;
	flag = 0;
	if (*str == '|' || *str == '&')
		return (1);
	while (*str)
	{
		quote_counter(*str, &s_count, &d_count);
		if (*str == '|' && are_counts_odd(d_count, s_count))
		{
			if (flag)
				return (1);
			flag = 1;
		}
		else if (!space(*str))
			flag = 0;
		str++;
	}
	if (flag)
		return (1);
	return (0);
}

int	check_quotes(char *str)
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
