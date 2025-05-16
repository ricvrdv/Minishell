/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 13:02:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/16 13:23:35 by Jpedro-c         ###   ########.fr       */
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
		ft_exit_child(mini, NULL);
		close_fds();
		exit_code(126, 1, 1);
	}
	else
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		ft_exit_child(mini, NULL);
		close_fds();
		exit_code(127, 1, 1);
	}
	return (0);
}

int	handle_error(char *temp, const char *error_message)
{
	ft_putstr_fd((char *)error_message, 2);
	free(temp);
	return (exit_code(2, 1, 0));
}
bool should_expand(const char *str)
{
    bool in_single;
    bool in_double;
    size_t i;

        i = 0;
        in_double = false;
        in_single = false;
    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
            in_single = !in_single;
        else if (str[i] == '"' && !in_single)
            in_double = !in_double;
        else if (str[i] == '$' && !in_single)
            return true;
        i++;
    }
    return false;
}

char	*strip_quotes(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'')
			|| (str[0] == '"' && str[len - 1] == '"')))
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
