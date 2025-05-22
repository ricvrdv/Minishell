/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:52:29 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/21 23:38:46 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tree	*new_tree_node(t_type type)
{
	t_tree	*node;

	node = safe_malloc(sizeof(t_tree));
	node->type = type;
	node->file_type = 0;
	node->argcount = 0;
	node->bad_herdoc = 0;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	node->hd_file = NULL;
	return (node);
}

t_tree	*create_arg_node(t_token *token)
{
	t_tree	*node;

	node = safe_malloc(sizeof(t_tree));
	node->type = token->type;
	node->file_type = 0;
	node->argcount = 0;
	node->args = safe_malloc(sizeof(char *) * 2);
	node->args[0] = token->value;
	node->args[1] = NULL;
	node->left = NULL;
	node->right = NULL;
	node->hd_file = NULL;
	node->bad_herdoc = 0;
	free(token);
	return (node);
}

t_tree	*create_redirection_node(t_token **tokens, t_token *temp)
{
	t_tree	*redi_node;

	redi_node = new_tree_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redi_node->file_type = 0;
	redi_node->left = parse_redirect(tokens);
	redi_node->right = create_arg_node(temp->next);
	redi_node->argcount = 0;
	redi_node->hd_file = NULL;
	redi_node->bad_herdoc = 0;
	free(temp->value);
	free(temp);
	return (redi_node);
}

t_tree	*especial_node(t_token **tokens, t_token *temp)
{
	t_tree	*redi_node;
	t_token	*redir_token;

	redir_token = temp->next->next;
	redi_node = new_tree_node((*tokens)->type);
	*tokens = (*tokens)->next;
	redi_node->file_type = 0;
	if (*tokens)
		redi_node->right = create_arg_node(*tokens);
	if (redir_token)
		redi_node->left = parse_redirect(&redir_token);
	redi_node->hd_file = NULL;
	redi_node->bad_herdoc = 0;
	free(temp->value);
	free(temp);
	return (redi_node);
}

int	found_sign(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '"')
				return (1);
			if (ft_isdigit(str[i + 1]))
				return (1);
			if (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?')
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}
