/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:56:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 13:52:04 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_env_node(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;

	new_node = safe_malloc(sizeof(t_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = *env_list;
	*env_list = new_node;
}

void	add_token_node(t_token **tokens, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}
