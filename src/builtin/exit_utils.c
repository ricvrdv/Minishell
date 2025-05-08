#include "../../inc/minishell.h"

static int	ft_numlen(long n);
static long	atol_digit_accumulate(const char *str, int sign);
static void	fill_ltoa_buf(long n, char *buf, int i);
static void	ft_ltoa_buf(long n, char *buf);

int	is_valid_long(const char *str)
{
	long	n;
	char	buf[22];

	if (*str == '+')
		str++;
	if (ft_strcmp(str, "-9223372036854775808") == 0)
		return (1);
	n = ft_atol(str);
	ft_ltoa_buf(n, buf);
	if (*str == '-' && ft_strcmp(str, buf) == 0)
		return (1);
	if (*str != '-' && ft_strcmp(str, buf + (*buf == '+')) == 0)
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	return (sign * atol_digit_accumulate(nptr + i, sign));
}

static long	atol_digit_accumulate(const char *str, int sign)
{
	long	result;
	int		i;
	int		digit;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > (LONG_MAX - digit) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
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
	int	len;

	if (n == LONG_MIN)
	{
		ft_strlcpy(buf, "-9223372036854775808", 22);
		return ;
	}
	len = ft_numlen(n);
	buf[len] = '\0';
	if (n == 0)
	{
		buf[0] = '0';
		buf[1] = '\0';
		return ;
	}
	fill_ltoa_buf(n, buf, len);
}

static void	fill_ltoa_buf(long n, char *buf, int i)
{
	if (n < 0)
	{
		buf[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		i--;
		buf[i] = (n % 10) + '0';
		n /= 10;
	}
}

long	calculate_exit_status(const char *arg)
{
	long	status;

	if (*arg == '+')
		arg++;
	status = ft_atol(arg);
	status %= 256;
	if (status < 0)
		status += 256;
	return (status);
}
