/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:39:14 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 11:52:25 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
	{
		i++;
	}
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
	{
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    char dest[20] = "Hello, ";
    const char *src = "world!";
    size_t size = 20;

    size_t result = ft_strlcat(dest, src, size);
    printf("Resulting string: %s\n", dest); 
    printf("Total length: %zu\n", result);

    return 0;
}
*/
