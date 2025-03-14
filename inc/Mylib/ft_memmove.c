/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:15:29 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 11:19:48 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	if (dest == src)
	{
		return (dest);
	}
	if (s < d)
	{
		while (n--)
		{
			*(d + n) = *(s + n);
		}
		return (dest);
	}
	while (n --)
	{
		*d++ = *s++;
	}
	return (dest);
}
/*
#include <stdio.h>

int main(void)
{
    char src[] = "Hello, world!";
    char dest[20];

    ft_memmove(dest, src, 13);
    printf("%s\n", dest); 
    return 0;
}
*/
