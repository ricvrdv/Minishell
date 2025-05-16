/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:00:13 by jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/16 17:22:35 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>

void	ft_putstr_fd(char *s, int fd)
{
	ssize_t ret;
	size_t len;

	if (!s)
		return;

	len = ft_strlen(s);
	ret = write(fd, s, len);
	if (ret == -1 && errno == EPIPE)
		return; // Avoid SIGPIPE crash
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

    ft_putstr_fd("Hello, world!", fd);

    close(fd);
    return 0;
}
*/
