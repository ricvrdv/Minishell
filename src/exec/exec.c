/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/20 16:36:49 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_node(t_tree *tree, t_minishell *mini, int in_fd, int out_fd)
{
	if (tree->type == PIPE)
		return (execute_pipe(tree, mini));
	else if (tree->type == REDIRECT_L || tree->type == REDIRECT_R
		|| tree->type == APPEND || tree->type == HEREDOC)
		return (execute_redirect(tree, mini, in_fd, out_fd));
	else if (tree->type == WORD)
		return (execute_command(tree, mini, in_fd, out_fd));
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

static int	handle_child(t_tree *node, t_minishell *mini)
{
	char	*full_path;
	int		status;

	status = 0;
	mini->is_child = true;
	clean_args_expand(node->args);
	ft_sig_child();
	if (!node->args[0])
		return (0);
	if (node->args[0][0] == '\0')
		invalid_cmd(mini);
	if (is_builtin(node->args[0]))
		exit(execute_builtin(node, mini));
	full_path = find_cmd_path(node->args[0], find_path_variable(mini), mini);
	if (!full_path)
		invalid_path(mini, node);
	if (execve(full_path, node->args, mini->env_array) == -1)
	{
		free(full_path);
		execve_fail(mini);
	}
	ft_sig_restore();
	exit (status);
}

int	handle_parent(pid_t pid)
{
	int	status;
	int	sig;

	ft_sig_mute();
	waitpid(pid, &status, 0);
	ft_sig_restore();
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			exit_code(130, 1, 0);
			return (-1);
		}
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 1);
			exit_code(131, 1, 0);
			return (-1);
		}
	}
	return (status);
}

int	execute_command(t_tree *node, t_minishell *mini, int in_fd, int out_fd)
{
	int			status;
	int			saved_stdin;
	int			saved_stdout;
	pid_t		pid;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	setup_cmd(node, in_fd, out_fd);
	if (is_builtin(node->args[0]))
		check_builtin(&status, node, mini);
	else if (mini->is_child)
		status = handle_child(node, mini);
	else
	{
		pid = fork();
		if (pid == 0)
			return (handle_child(node, mini));
		status = handle_parent(pid);
		if (status == -1)
			return (0);
	}
	ft_sig_restore();
	restore_fd(saved_stdin, saved_stdout);
	return (exit_code(status, 1, 0));
}
