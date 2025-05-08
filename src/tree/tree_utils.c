/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:52:29 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/07 13:45:31 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

s_tree	*new_tree_node(s_type type)
{
	s_tree	*node;

	node = safe_malloc(sizeof(s_tree));
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

s_tree	*create_arg_node(s_token *token)
{
	s_tree	*node;

	node = safe_malloc(sizeof(s_tree));
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

s_tree	*create_redirection_node(s_token **tokens, s_token *temp)
{
	s_tree	*redi_node;

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

s_tree	*especial_node(s_token **tokens, s_token *temp)
{
	s_tree	*redi_node;

	redi_node = new_tree_node((*tokens)->type);
	*tokens = (*tokens)->next->next;
	redi_node->file_type = 0;
	redi_node->left = parse_redirect(tokens);
	redi_node->right = create_arg_node(temp->next);
	redi_node->hd_file = NULL;
	redi_node->bad_herdoc = 0;
	free(temp->value);
	free(temp);
	return (redi_node);
}

int verify_permissions(s_tree *tree, s_minishell *mini)
{
	int	status;
	char *path;

	path = NULL;
	status = 0;
	if(tree->args && !is_builtin(tree->args[0]) && (tree->file_type == READ_FILE || tree->file_type == APPEND_FILE))
	{
		path = find_cmd_path(tree->args[0], find_path_variable(mini));
		if(!path)
			return 127;
		if(access(path, F_OK) != 0)
			return 127;
		if (is_directory(path))
			return 126;
		if (access(path, X_OK) != 0)	
			return 126;
		free(path);
	}
	if(status == 0 && tree->right)
		status = verify_permissions(tree->right, mini);
	return (status);
}
