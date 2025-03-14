/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:08:08 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/12 15:13:25 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_prints(char *str)
{
	int	count;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	count = 0;
	while (*str)
	{
		write(1, str, 1);
		count++;
		str++;
	}
	return (count);
}

/*
int main ()
{
	char *new = NULL;

	int count_printf = printf("%s", new);
	printf("\n");
	int count_prints = ft_prints(new);
	printf("\n");

	printf("\nCount from printf: %i\n", count_printf);

	printf("\nCount from ft_prints: %i\n", count_prints);
}
*/
