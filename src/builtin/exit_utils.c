#include "../../inc/minishell.h"

static int	ft_numlen(long n);
static void	ft_ltoa_buf(long n, char *buf);

int	is_valid_long(const char *str)
{
	long	n;
	char	buf[22];

	if (ft_strcmp(str, "-9223372036854775808") == 0)
		return (1);
    n = ft_atol(str);
	ft_ltoa_buf(n, buf);
	if (ft_strcmp(str, buf) == 0)
		return (1);
	return (0);
}

long    ft_atol(const char *nptr)
{
	int	    i;
	long	result;
	int	    sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result > (LONG_MAX - (nptr[i] - '0')) / 10)
        {
            if (sign == 1)
                return (LONG_MAX);
            else
                return (LONG_MIN);
        }
        result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

static int	ft_numlen(long n)
{
	int	len = 0;

	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_ltoa_buf(long n, char *buf)
{
	int		len;
	int		i;

	len = ft_numlen(n);
    i = len;
    buf[i] = '\0';
	if (n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return ;
	}
    if (n == LONG_MIN)
    {
        ft_strlcpy(buf, "-9223372036854775808", 22);
        return ;
    }
	while (n)
	{
		if (n > 0)
			buf[--i] = (n % 10) + '0';
		else
			buf[--i] = -(n % 10) + '0';
		n /= 10;
	}
	if (buf[0] != '-' && i > 0)
		buf[--i] = '-';
}
