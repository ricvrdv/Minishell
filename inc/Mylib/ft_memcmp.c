/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:15:48 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 14:36:50 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*c1;
	const unsigned char	*c2;
	size_t				i;

	i = 0;
	c1 = (const unsigned char *)s1;
	c2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (c1[i] != c2[i])
		{
			return (c1[i] - c2[i]);
		}
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int main(void)
{
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "World";

    printf("%i\n", ft_memcmp(str1, str2, 5)); 
    printf("%i\n", ft_memcmp(str1, str3, 5)); // -15 
    return 0;
}
*/
