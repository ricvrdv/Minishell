/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:04:04 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 11:18:34 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	new;

	if ((nmemb == 0) || (size == 0))
	{
		return ((malloc)(0));
	}
	new = (nmemb * size);
	ptr = malloc(new);
	if (!ptr)
	{
		return (NULL);
	}
	ft_memset(ptr, 0, new);
	return ((void *)ptr);
}
/*
#include <stdio.h>
#include "libft.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    int *arr = (int *)ft_calloc(5, sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
    free(arr);
    return 0;
}
*/
