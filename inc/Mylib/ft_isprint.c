/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:12:20 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 10:14:16 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
    printf("%i\n", ft_isprint('a'));
    printf("%i\n", ft_isprint('1'));
    printf("%i\n", ft_isprint(20));
    return 0;
}
*/
