/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:58:18 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 11:11:33 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*srcc;

	if ((dest == src) || (n == 0))
	{
		return (dest);
	}
	if (!dest && !src)
	{
		return (0);
	}
	dst = (char *)dest;
	srcc = (const char *)src;
	while (n--)
	{
		dst[n] = srcc[n];
	}
	return (dest);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    char src[] = "Hello, world!";
    char dest[20];

    ft_memcpy(dest, src, 13);
    printf("%s\n", dest); 
    return 0;
}
*/
