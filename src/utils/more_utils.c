/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:02:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/08 13:04:30 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_cmd_access(const char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	else if (access(cmd, F_OK) == 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		exit(126);
	}
	else
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		exit(127);
	}
}