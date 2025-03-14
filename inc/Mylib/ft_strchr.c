/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:55:04 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 12:14:51 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s + i);
	}
	return (0);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    const char *str = "Hello, world!";
    char *result;

    result = ft_strchr(str, 'o');
    if (result)
        printf("Found 'o' at: %s\n", result); 

    result = ft_strchr(str, '\0');
    if (result)
        printf("Found null terminator at: %s\n", result); 

    return 0;
}
*/
