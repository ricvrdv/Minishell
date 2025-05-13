/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:55:57 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/13 12:27:40 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	invalid_operator(char **str)
{
	char	*start;

	start = *str;
	(*str)++;
	if (*start == **str)
		(*str)++;
	*str = s_spaces(*str);
	if (**str == '\0' || **str == '>' || **str == '|' || **str == '<')
		return (1);
	return (0);
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i = i + 1;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	*jump_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

s_tree	*parse_token(s_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipe(tokens));
}
