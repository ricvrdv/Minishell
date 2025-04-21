/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printint_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:27:53 by icunha-t          #+#    #+#             */
/*   Updated: 2025/04/21 11:57:54 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printint_hex(char spec, unsigned int n, int fd)
{
	int		r;
	char	*hexa;

	r = 0;
	if (spec == 'X')
		hexa = HEX_UPP;
	else
		hexa = HEX_LOW;
	if (n >= 16)
	{
		r = r + ft_printint_hex(spec, n / 16, fd);
		r = r + ft_printint_hex(spec, n % 16, fd);
	}
	else
		r = r + ft_printchar (hexa[n], fd);
	return (r);
}
