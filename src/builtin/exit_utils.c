#include "../../inc/minishell.h"

static int	ft_numlen(long n);
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
