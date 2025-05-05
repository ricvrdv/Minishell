/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:53:27 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/02 11:52:15 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	report_error(int status)
{
	return (status);
}

int	exit_code(int exit_status, int write_, int exit_)
{
	static int	current_status;

	if (write_ == 1)
		current_status = exit_status;
	if (exit_ == 1)
		exit(current_status);
	return (current_status);
}

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}