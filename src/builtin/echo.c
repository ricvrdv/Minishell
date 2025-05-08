#include "../../inc/minishell.h"

static void	print_arguments(s_tree *node, int start_index);

int	mini_echo(s_tree *node)
{
	int	n_flag;
	int	i;
	int	j;

	n_flag = 0;
	i = 1;
	while (i < node->argcount && node->args[i][0] == '-'
		&& node->args[i][1] == 'n')
	{
		j = 1;
		while (node->args[i][j] == 'n')
			j++;
		if (node->args[i][j] != '\0')
			break ;
		n_flag = 1;
		i++;
	}
	print_arguments(node, i);
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

static void	print_arguments(s_tree *node, int start_index)
{
	int	i;

	i = start_index;
	while (i < node->argcount)
	{
		ft_putstr_fd(node->args[i], STDOUT_FILENO);
		if (i + 1 < node->argcount)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
}
