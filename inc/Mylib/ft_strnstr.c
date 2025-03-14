/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:37:30 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 14:47:10 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		c;
	size_t		n_len;
	const char	*ptr;

	i = 0;
	ptr = (const char *)big;
	n_len = ft_strlen(little);
	if (n_len == 0 || big == little)
		return ((char *)(ptr));
	while (ptr[i] != '\0' && i < len)
	{
		c = (0);
		while (ptr[i + c] != '\0' && little[c] != '\0'
			&& ptr[i + c] == little[c] && i + c < len)
		{
			c++;
		}
		if (c == n_len)
		{
			return ((char *)(ptr + i));
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
    const char *big = "Hello, world!";
    const char *little = "world";
    size_t len = 12;

    char *result = ft_strnstr(big, little, len);
    if (result)
    {
        printf("Found substring: %s\n", result);
    }
    else
    {
        printf("Substring not found\n");
    }

    return 0;
}
*/
