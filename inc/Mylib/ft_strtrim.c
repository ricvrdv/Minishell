/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:08:21 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 12:27:23 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;
	char	*str;

	if (!s1)
	{
		return (NULL);
	}
	if (!set)
	{
		return (ft_strdup(s1));
	}
	first = 0;
	last = (ft_strlen(s1) - 1);
	while (s1[first] && ft_strchr(set, s1[first]))
		++first;
	while (s1[first] && ft_strchr(set, s1[last]))
		--last;
	if (first > last)
		return (ft_strdup(""));
	str = ft_substr(s1, first, ((last - first) + 1));
	return (str);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    const char *s1 = "  Hello, world!  ";
    const char *set = " ";

    char *result = ft_strtrim(s1, set);
    if (result)
    {
        printf("Trimmed string: '%s'\n", result); // Should print "Hello, world!"
        free(result);
    }
    else
    {
        printf("Trimming failed\n");
    }

    return 0;
}
*/
