/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:05:32 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 14:07:15 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
#include <fcntl.h>
#include "libft.h"

int main(void)
{
    int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
    {
        return 1; // Error opening file
    }

    ft_putchar_fd('H', fd);
    ft_putchar_fd('i', fd);
    ft_putchar_fd('\n', fd);

    close(fd);
    return 0;
}
*/
