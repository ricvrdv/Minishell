/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:32:37 by root              #+#    #+#             */
/*   Updated: 2025/04/21 11:58:17 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_printstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_printstr("(null)", fd));
	while (str[i])
	{
		ft_printchar(str[i], fd);
		i++;
	}
	return (i);
}
