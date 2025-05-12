/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:34 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/12 23:07:45 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void remove_quotes(char *arg)
{
	char *read_ptr = arg;
	char *write_ptr = arg;
	int in_single = 0;
	int in_double = 0;

	while (*read_ptr)
	{
		if (*read_ptr == '\'' && !in_double)
		{
			in_single = !in_single;
			read_ptr++; 
		}
		else if (*read_ptr == '"' && !in_single)
		{
			in_double = !in_double;
			read_ptr++;
		}
		else
			*write_ptr++ = *read_ptr++;
	}
	*write_ptr = '\0';
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

void	clean_args(char **args, int arg_count)
{
	int	index;

	index = 0;
	while (index < arg_count)
	{
		remove_quotes(args[index]);
		index++;
	}
}

