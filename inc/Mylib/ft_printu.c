/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <jpedro-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:53:12 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/13 15:07:00 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printu(unsigned int n)
{
	char	r;
	int		len;

	len = 0;
	if (n < 10)
	{
		r = n + '0';
		write(1, &r, 1);
		len++;
	}
	else
	{
		len += ft_printu (n / 10) + 1;
		r = (n % 10) + '0';
		write(1, &r, 1);
	}
	return (len);
}
/*
int main ()
{
	int teste = -1;
	int lenu;
	int lenf;
	
	lenu = ft_printu(teste);
	printf("\n");

	lenf = printf("%u", teste);
	printf("\n");


	printf("Lenght in my ft_: %d", lenu);
	printf("\n");

	printf("Lenght in printf: %d", lenf);
	printf("\n");
}
*/
