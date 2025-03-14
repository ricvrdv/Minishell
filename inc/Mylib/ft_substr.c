/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:21:03 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 11:34:38 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	remain_len;

	remain_len = ft_strlen(s) - start;
	if (!s)
		return (NULL);
	if (len > remain_len)
		len = remain_len;
	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	new = malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!new)
		return (0);
	while (i < len)
	{
		new[i] = *(s + start + i);
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
#include <stdio.h>
#include "libft.h"

int main(void)
{
    const char *s = "Hello, world!";
    unsigned int start = 7;
    size_t len = 5;

    char *result = ft_substr(s, start, len);
    if (result)
    {
        printf("Substring: '%s'\n", result); // Should print "world"
        free(result);
    }
    else
    {
        printf("Substring extraction failed\n");
    }

    return 0;
}
*/
