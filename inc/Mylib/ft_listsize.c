/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:43:34 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/12/05 12:48:54 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_listsize(t_list *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
	{
		return (0);
	}
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
