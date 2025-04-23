/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:59 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/23 21:44:14 by joaorema         ###   ########.fr       */
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

char	*strip_quotes_and_join(char *input)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = safe_malloc(ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] != '"')
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*join_args(char **args)
{
	char	*joined;
	char	*tmp;
	int		i;

	i = 0;
	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while (args[i])
	{
		tmp = safe_malloc(ft_strlen(joined) + ft_strlen(args[i]) + 1);
		tmp[0] = '\0';
		strcat(tmp, joined);
		strcat(tmp, args[i]);
		free(joined);
		joined = tmp;
		i++;
	}
	return (joined);
}
