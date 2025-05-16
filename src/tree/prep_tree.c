/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:51:58 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/16 15:17:26 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	preprocess_tree(s_tree *tree, s_minishell *mini)
{
	int	counter[12];
	int status;
	pid_t pid;
	int ret;
	
	rename_nodes(tree);
	init_pipes_array(counter, 1);
	count_pipes_redir(tree, counter);
	init_pipes_array(counter, 0);
	mini->root = tree;
	mini->heredoc_count = counter[2];
	assign_heredoc_filenames(tree);
	if (mini->heredoc_count > 0)
	{
		pid = fork();
		if(pid == 0)
		{
			ft_sig_child_heredoc(mini);
			ret = handle_heredocs(tree, mini);
			ft_exit_child(mini, NULL);
			if(ret == -5)
				exit(130);
			exit(0);
		}
		else
		{
			waitpid(pid, &status, 0);
            if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
            {
                tree->bad_herdoc = 1;
                return;
            }
            else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            {
                tree->bad_herdoc = 1;
                return;
            }
		}
	}
}

void	prep_tree(s_tree *tree, s_minishell *mini, int *status)
{
	int	first_check;

	first_check = 0;
	preprocess_tree(tree, mini);
	if (tree->bad_herdoc == 1)
	{
		return ;
	}
	expand_tree(mini, tree);
	if (first_check == 0)
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
		while (i < 6)
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

void assign_heredoc_filenames(s_tree *tree)
{
    if (!tree)
        return;
    if (tree->type == HEREDOC && tree->right)
    {
        // Only assign if not already assigned (for safety)
        if (!tree->right->hd_file)
            tree->right->hd_file = generate_file(static_index());
    }
    assign_heredoc_filenames(tree->left);
    assign_heredoc_filenames(tree->right);
}
