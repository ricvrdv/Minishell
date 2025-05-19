/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:46:17 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 14:46:50 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_sigint(void)
{
	ft_putstr_fd("\n", 1);
	exit_code(130, 1, 0);
}

void	print_sigquit(void)
{
	ft_putstr_fd("Quit (core dumped)\n", 1);
	exit_code(131, 1, 0);
}

void	check_builtin(int *status, t_tree *tree, t_minishell *mini) //
{
	*status = execute_builtin(tree, mini);
	exit_code(*status, 1, 0);
}

void	assign_heredoc_filenames(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->type == HEREDOC && tree->right)
	{
		if (!tree->right->hd_file)
			tree->right->hd_file = generate_file(static_index());
	}
	assign_heredoc_filenames(tree->left);
	assign_heredoc_filenames(tree->right);
}

void	handle_heredoc_fork(pid_t pid, t_tree *tree, t_minishell *mini)
{
	int	status;
	int	ret;

	if (pid == 0)
	{
		ft_sig_child_heredoc(mini);
		ret = handle_heredocs(tree, mini);
		ft_exit_child(mini, NULL);
		if (ret == -5)
			exit(130);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) != 0))
		tree->bad_herdoc = 1;
}
