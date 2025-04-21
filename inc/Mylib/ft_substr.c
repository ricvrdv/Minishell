/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:21:03 by jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 12:01:38 by Jpedro-c         ###   ########.fr       */
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
