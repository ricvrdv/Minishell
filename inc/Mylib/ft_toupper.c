/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:54:46 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/21 15:56:06 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    printf("%i\n", ft_toupper('a'));
    printf("%i\n", ft_toupper('1'));
    printf("%i\n", ft_toupper('!'));
    return 0;
}
*/
