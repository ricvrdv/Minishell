#include "../../inc/minishell.h"

static void	handle_exit_cleanup(s_minishell *mini, s_tree *node, int code);
static int	handle_args_offset(s_tree *node);
static bool	is_numeric_arg_valid(const char *arg);
static void	exit_error(const char *arg, bool numeric_error);

int	mini_exit(s_minishell *mini, s_tree *node)
{
	int		arg_offset;
	long	exit_status;

	if (!mini->is_child)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (mini->is_child)
	{
		exit_status = extra_mini_exit(mini, node);
		return (exit_code(exit_status, 1, 0));
	}
	arg_offset = handle_args_offset(node);
	if (arg_offset == -1)
		handle_exit_cleanup(mini, node, 0);
	if (!is_numeric_arg_valid(node->args[arg_offset]))
	{
		exit_error(node->args[arg_offset], true);
		handle_exit_cleanup(mini, node, 2);
	}
	if (node->argcount > arg_offset + 1)
	{
		exit_error(NULL, false);
		return (1);
	}
	exit_status = calculate_exit_status(node->args[arg_offset]);
	handle_exit_cleanup(mini, node, (int)exit_status);
	return ((int)exit_status);
}
static void	handle_exit_cleanup(s_minishell *mini, s_tree *node, int code)
{
	free_struct(mini);
	free(mini);
	clear_history();
	clear_tree(&node);
	close(4);
	close(3);
	close(5);
	close(6);
	exit_code(code, 1, 1);
}

static int	handle_args_offset(s_tree *node)
{
	if (node->argcount == 1)
		return (-1);
	if (ft_strcmp(node->args[1], "--") == 0)
	{
		if (node->argcount == 2)
			return (-1);
		else
			return (2);
	}
	return (1);
}

static bool	is_numeric_arg_valid(const char *arg)
{
	int		i;
	bool	has_sign;

	i = 0;
	has_sign = false;
	if (arg[i] == '+' || arg[i] == '-')
	{
		has_sign = true;
		i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	if (has_sign && i == 1)
		return (false);
	if (arg[0] == '+')
		return (is_valid_long(arg + 1));
	return (is_valid_long(arg));
}

static void	exit_error(const char *arg, bool numeric_error)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (numeric_error)
	{
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code(2, 1, 0);
	}
	else
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
}

int	extra_mini_exit(s_minishell *mini, s_tree *node)
{
	int		arg_offset;
	long	exit_status;

	if (!mini->is_child)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	arg_offset = handle_args_offset(node);
	if (arg_offset == -1)
		return (exit_code(0, 1, 0));
	if (!is_numeric_arg_valid(node->args[arg_offset]))
	{
		exit_error(node->args[arg_offset], true);
		return (exit_code(0, 0, 0));
	}
	if (node->argcount > arg_offset + 1)
		return (exit_code(1, 1, 0));
	exit_status = calculate_exit_status(node->args[arg_offset]);
	return ((int)exit_status);
}
