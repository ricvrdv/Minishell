/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:40:15 by jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 12:00:06 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_1;
	size_t	len_2;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 || !s2)
	{
		return (NULL);
	}
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_1 + len_2 + 1));
	if (!str)
	{
		return (NULL);
	}
	ft_memcpy(str, s1, len_1);
	ft_memcpy((str + len_1), s2, len_2);
	str[len_1 + len_2] = '\0';
	return (str);
}
