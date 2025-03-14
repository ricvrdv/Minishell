/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:12:31 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 11:23:10 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c < 0 || c > 127)
	{
		return (0);
	}
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
    printf("%i\n", ft_isalpha('a'));
    printf("%i\n", ft_isalpha('1'));
    printf("%i\n", ft_isalpha('!'));
    return 0;
}
*/
