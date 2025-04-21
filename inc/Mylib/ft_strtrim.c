/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:08:21 by jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 12:01:31 by Jpedro-c         ###   ########.fr       */
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
