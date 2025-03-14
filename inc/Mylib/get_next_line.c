/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:42:35 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/11/20 12:39:16 by jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*dest;

	dest = ft_strjoingnl(buffer, buf);
	free(buffer);
	return (dest);
}

char	*file_read(int fd, char *txt)
{
	char	*buffer;
	int		bytes_read;

	if (!txt)
		txt = ft_callocgnl(1, 1);
	buffer = ft_callocgnl(BUFFER_SIZE + 1, sizeof(char));
	if (!txt || !buffer)
		return (free(buffer), free(txt), NULL);
	bytes_read = 0;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(txt), NULL);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = 0;
		txt = ft_free(txt, buffer);
		if (!txt)
			return (free(buffer), NULL);
		if (ft_strchrgnl(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (txt);
}

char	*ft_extract(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_callocgnl(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_callocgnl(ft_strlengnl(buffer) - i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = file_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract(buffer);
	buffer = ft_next(buffer);
	return (line);
}
