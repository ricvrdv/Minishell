/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:37:30 by jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/21 12:01:22 by Jpedro-c         ###   ########.fr       */
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
