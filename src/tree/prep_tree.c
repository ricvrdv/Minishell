/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:51:58 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/04/30 11:26:29 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	prep_tree(s_tree *tree, s_minishell *mini, int *status)
{
	int	counter[12];
	int first_check;

	first_check = 0;
	rename_nodes(tree);
	init_pipes_array(counter, 1);
	count_pipes_redir(tree, counter);
	init_pipes_array(counter, 0);
	mini->heredoc_count = counter[2];
	while(mini->heredoc_count)
	{
		first_check = handle_heredocs(tree);
		mini->heredoc_count = 0;
	}
	expand_tree(mini, tree);
	first_check = verify_permissions(tree, mini);
	if(first_check == 0)
		*status = execute_node(tree, mini, STDIN_FILENO, STDOUT_FILENO);
}

void	count_pipes_redir(s_tree *tree, int *counter)
{
	tree->file_type = 0;
	if (tree->type == PIPE)
		counter[5] += 1;
	else if (tree->type == REDIRECT_R || tree->type == APPEND)
		counter[4] += 1;
	else if (tree->type == REDIRECT_L)
		counter[3]++;
	else if (tree->type == HEREDOC)
		counter[2]++;
	if (tree->left)
		count_pipes_redir(tree->left, counter);
	if (tree->right)
		count_pipes_redir(tree->right, counter);
}

void	init_pipes_array(int *counter, int flag)
{
	int	i;

	i = 0;
	if (flag)
		while (i < 12)
			counter[i++] = 0;
	else if (counter[5])
		counter[0] = counter[0] + 1;
}

void	rename_nodes(s_tree *tree)
{
	if (tree->type != WORD)
	{
		tree->file_type = TREE_READY;
		if (tree->type == REDIRECT_R && tree->right)
			tree->right->file_type = WRITE_FILE;
		if (tree->type == APPEND && tree->right)
			tree->right->file_type = APPEND_FILE;
		if (tree->type == REDIRECT_L && tree->right)
			tree->right->file_type = READ_FILE;
		if (tree->type == HEREDOC && tree->right)
			tree->right->file_type = HEREDOC_FILE;
		if (tree->type == PIPE)
		{
			if (tree->right)
				tree->right->file_type = CMD_READY;
			if (tree->left)
				tree->left->file_type = CMD_READY;
		}
	}
	if (!tree->file_type)
		tree->file_type = CMD_READY;
	if (tree->left)
		rename_nodes(tree->left);
	if (tree->right)
		rename_nodes(tree->right);
}

s_tree	*parse_token(s_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	return (parse_pipe(tokens));
}

int handle_heredocs(s_tree *tree)
{
	int fd;
	
	if(!tree)
		return 1;
	if(tree->type == HEREDOC)
	{
		fd = handle_heredoc(tree);
		close(fd);	
	}
	if(tree->left)
		handle_heredocs(tree->left);
	if(tree->right)
		handle_heredocs(tree->right);
	return 0;
}

