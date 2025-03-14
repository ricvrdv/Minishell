/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:59:42 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/21 16:09:11 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c < 0 || c > 127)
	{
		return (0);
	}
	if (c >= '0' && c <= '9')
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
    printf("%i\n", ft_isdigit('a'));
    printf("%i\n", ft_isdigit('1'));
    printf("%i\n", ft_isdigit('!'));
    return 0;
}
*/
