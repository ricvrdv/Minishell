/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:02:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/12 23:22:14 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_cmd_access(const char *cmd, s_minishell *mini)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (0);
	else if (access(cmd, F_OK) == 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		ft_exit_child(mini , NULL);
		close_fds();
		exit_code(126, 1, 1);
	}
	else
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ft_exit_child(mini , NULL);
		close_fds();
		exit_code(127, 1, 1);
	}
	return 0;
}