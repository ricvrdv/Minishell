/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:41:53 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 10:53:18 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*new;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new)
	{
		return (NULL);
	}
	while (*s)
	{
		new[i] = *s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
/*
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	char *new;

	if(argc == 2)
	{
		new = ft_strdup(argv[1]);
		printf("%s\n", new);
	}
	return 0;
}
*/
