/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:08:59 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 10:10:48 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    printf("%i\n", ft_isascii('a'));
    printf("%i\n", ft_isascii('1'));
    printf("%i\n", ft_isascii(200));
    return 0;
}
*/
