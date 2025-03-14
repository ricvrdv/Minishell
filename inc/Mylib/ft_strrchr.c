/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:08:14 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/22 13:23:38 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == '\0')
	{
		return ((char *)s + i);
	}
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    const char *str = "Hello, world!";
    int ch = 'o';

    char *result = ft_strrchr(str, ch);
    if (result)
    {
        printf("Last occurrence of '%c': %s\n", ch, result);
    }
    else
    {
        printf("Character not found\n");
    }

    return 0;
}
*/
