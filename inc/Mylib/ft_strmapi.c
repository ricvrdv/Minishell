/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpedro-c <jpedro-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:35:06 by jpedro-c          #+#    #+#             */
/*   Updated: 2024/10/24 11:44:21 by passunca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (s == NULL || f == NULL)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
#include "libft.h"

char sample_function(unsigned int i, char c)
{
    return c + 13;   /// rot13 por exemplo
}

int main(void)
{
    const char *str = "Hello, world!";
    char *result = ft_strmapi(str, sample_function);
    if (result)
    {
        printf("%s\n", result); 
        free(result);
    }
    return 0;
}
*/
