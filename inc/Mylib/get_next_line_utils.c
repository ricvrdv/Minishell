/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:43:42 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/18 13:15:10 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoingnl(char const *s1, char const *s2)
{
	int		size;
	char	*rest;
	int		i;
	int		j;

	size = ft_strlen(s1) + ft_strlen(s2);
	rest = malloc(sizeof(char) * (size + 1));
	if (!rest || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		rest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		rest[i] = s2[j];
		i++;
		j++;
	}
	rest[size] = 0;
	return (rest);
}

char	*ft_strchrgnl(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && *str != 0)
		str++;
	if (*str == c)
		return (str);
	else
		return (NULL);
}

void	ft_bzerognl(void *s, size_t n)
{
	size_t			i;
	char			*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*ft_callocgnl(size_t nmemb, size_t size)
{
	char	*rest;

	rest = malloc(nmemb * size);
	if (!rest)
		return (NULL);
	ft_bzero(rest, nmemb * size);
	return (rest);
}

size_t	ft_strlengnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
