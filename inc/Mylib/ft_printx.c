/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:34:04 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/13 16:05:46 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_printx(char type, unsigned long n, int base)
{
	int		count;
	char	*symbols;

	if (type == 'x')
		symbols = "0123456789abcdef";
	if (type == 'X')
		symbols = "0123456789ABCDEF";
	if (n < (unsigned int)base)
	{
		return (write(1, &symbols[n], 1));
	}
	else
	{
		count = ft_printx(type, n / base, base);
		return (count + ft_printx(type, n % base, base));
	}
	return (0);
}
/*
int main()
{
	int	teste = -1;
	int	len;
	int	lenf;

	len = ft_printx('x', teste, 16);
	printf("\n");

	lenf = printf("%x", teste);
	printf("\n");
	
	printf("Length on my ft_: %i\n", len);

	printf("Length on printf: %i\n", lenf);	
}
*/
