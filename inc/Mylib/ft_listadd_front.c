/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:34:42 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/12/05 12:43:11 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_listadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
	{
		return (NULL);
	}
	new->next = *lst;
	*lst = new;
}
