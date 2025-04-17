#include "../../inc/minishell.h"

int	fd_identifier(int *counter, int index, int index_2, int con)
{
	if (con)
	{
		if (counter[index])
			close(counter[index_2]);
		counter[index] = 1;
	}
	else
	{
		ft_putendl_fd("err: file not found", 2);
		counter[6] = 0;
	}
	return (1);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error with Malloc!");
	return (ret);
}

bool	are_counts_odd(int d_count, int s_count)
{
	return (!(d_count % 2) && !(s_count % 2));
}
int report_error(int status)
{
    return status;
}