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


void	remove_empty_args(char **args)
{
	int	i = 0;
	int	j = 0;

	while (args[i])
	{
		if (args[i][0] != '\0')
		{
			args[j++] = args[i];
		}
		else
			free(args[i]); // free empty string
		i++;
	}
	args[j] = NULL;
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
	//if(status == 0 && tree->left)
	//	status = verify_permissions(tree->left, mini);
	if(status == 0 && tree->right)
		status = verify_permissions(tree->right, mini);
	return (status);
}

int is_directory(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}