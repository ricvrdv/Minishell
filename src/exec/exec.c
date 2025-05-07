/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:00:23 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/07 10:53:59 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd)
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

static int	handle_child(s_tree *node, s_minishell *mini)
{
	char	*full_path;
	int 	status;

	status = 0;
	mini->is_child = true;
	clean_args_expand(node->args);
	if (!node->args[0])
		return (0); 
	if (node->args[0][0] == '\0')
	{
		ft_putstr_fd(" command not found\n", 2);
		close(4);
		close(3);
		clear_tree(&node);
		ft_exit_child(mini, NULL);
		exit(127);	
	}
	if (is_builtin(node->args[0]))
		exit(execute_builtin(node, mini));
	full_path = find_cmd_path(node->args[0], find_path_variable(mini));
	if (!full_path)
	{
		ft_putstr_fd(" command not found\n", 2);
		close(4);
		close(3);
		clear_tree(&node);
		ft_exit_child(mini, NULL);
		exit_code(127, 1, 1);
	}
	if (execve(full_path, node->args, mini->env_array) == -1)
	{
		ft_putstr_fd(" Is a directory\n", 2);
		close(3);
		close(4);
		clear_tree(&node);
		ft_exit_child(mini, NULL);
		status = (126);
		exit (status);
	}
	exit (status);
}

int	handle_parent(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd)
{
	int			status;
	int			saved_stdin;
	int			saved_stdout;
	pid_t		pid;

	status = 0;
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	redirect_fds(in_fd, out_fd);
	pre_clean_args(node->args, &node->argcount);
	clean_args(node->args, node->argcount);
	if (is_builtin(node->args[0]))
		status = execute_builtin(node, mini);
	else if(mini->is_child)
	{
		status = handle_child(node, mini);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (report_error(127));
		if (pid == 0)
			return (handle_child(node, mini));
		
		status = handle_parent(pid);
	}
	restore_fd(saved_stdin, saved_stdout);
	return (exit_code(status, 1, 0));
}

