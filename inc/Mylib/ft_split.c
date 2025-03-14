/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:02:45 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/25 11:11:16 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	s_malloc(char **words_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	words_v[position] = malloc(buffer);
	if (words_v[position] == NULL)
	{
		while (i < position)
		{
			free(words_v[i++]);
		}
		free(words_v);
		return (1);
	}
	return (0);
}

int	fill(char **words_v, char const *s, char sep)
{
	int		i;
	size_t	len;

	i = 0;
	if (words_v == NULL)
		return (0);
	while (*s)
	{
		len = 0;
		while (*s == sep && *s)
			++s;
		while (*s != sep && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (s_malloc(words_v, i, len + 1))
				return (1);
			ft_strlcpy(words_v[i], s - len, len + 1);
		}
		++i;
	}
	return (0);
}

size_t	count_words(char const *s, char sep)
{
	size_t	words;
	int		i_words;

	words = 0;
	while (*s)
	{
		i_words = 0;
		while (*s == sep && *s)
			++s;
		while (*s != sep && *s)
		{
			if (!i_words)
			{
				++words;
				i_words = 42;
			}
			++s;
		}
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**words_v;

	if (s == NULL)
	{
		return (NULL);
	}
	words = 0;
	words = count_words(s, c);
	words_v = malloc((words + 1) * sizeof(char *));
	if (words_v == NULL)
	{
		return (NULL);
	}
	words_v[words] = NULL;
	if (fill(words_v, s, c))
	{
		return (NULL);
	}
	return (words_v);
}

/*
int main()
{
	char	*s= "  Hello there my dudes!!";
	char	**v = ft_split(s, ' ');

	while(*v)
		printf("%s\n", *v++);
}
*/
