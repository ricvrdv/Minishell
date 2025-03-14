/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <jpedro-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:45:40 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/13 15:53:39 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printp(unsigned long pointer)
{
	unsigned long	n;
	int				len;
	int				base;

	n = pointer;
	base = 16;
	len = 0;
	if (!pointer)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	else
	{
		len = write(1, "0x", 2);
		len += ft_printx('x', n, base);
		return (len);
	}
	return (len);
}
/*
int main ()
{
    unsigned long teste = 100;
    int len;
    int lenf;

    len = ft_printp(teste);
    printf("\n");

    lenf = printf("%p", (void *)teste);
    printf("\n");

    printf("Length on my ft_: %i\n", len);
    printf("Length on printf: %i\n", lenf);    
}
*/
