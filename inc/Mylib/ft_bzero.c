/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:51:54 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 16:20:05 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>
#include <stddef.h>

//vai tornar os 3 primeiros caracters 0
int main(void)
{
    char str[10] = "Hello";
    ft_bzero(str, 3);
    for (int i = 0; i < 5; i++)
    {
        printf("%i ", str[i]);
    }
    printf("\n");
    return 0;
}
*/
