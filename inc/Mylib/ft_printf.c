/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:24:04 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/13 15:41:08 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	print_type(char type, va_list ap)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_printc(va_arg(ap, int));
	else if (type == 's')
		count += ft_prints(va_arg(ap, char *));
	else if (type == 'd')
		count += ft_printd(va_arg(ap, int));
	else if (type == 'p')
		count += ft_printp((unsigned long)va_arg(ap, void *));
	else if (type == 'i')
		count += ft_printd(va_arg(ap, int));
	else if (type == 'u')
		count += ft_printu(va_arg(ap, unsigned int));
	else if (type == 'x' || type == 'X')
		count += ft_printx(type, va_arg(ap, unsigned int), 16);
	else if (type == '%')
		count += ft_printc('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, str);
	count = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			if (*str == '\0')
				break ;
			count += print_type(*str, ap);
		}
		else
		{
			count += write(1, str, 1);
		}
		str++;
	}
	va_end(ap);
	return (count);
}
