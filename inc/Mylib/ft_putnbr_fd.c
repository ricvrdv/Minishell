/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:42:39 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/23 12:56:58 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
			ft_putnbr_fd(n, fd);
		}
		else if (n < 10)
		{
			c = n + '0';
			write(fd, &c, 1);
		}
		else
		{
			ft_putnbr_fd (n / 10, fd);
			c = (n % 10) + '0';
			write(fd, &c, 1);
		}
	}
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

    ft_putnbr_fd(12345, fd);
    ft_putnbr_fd(-6789, fd);
    ft_putnbr_fd(0, fd);

    close(fd);
    return 0;
}
*/
