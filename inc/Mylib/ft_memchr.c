/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:02 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 14:15:12 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    char str[] = "Hello, world!";
    char *result = ft_memchr(str, 'o', 13);
    if (result != NULL)
    {
        printf("Found 'o' at position: %ld\n", result - str);
    }
    else
    {
        printf("'o' not found\n");
    }
    return 0;
}
*/
