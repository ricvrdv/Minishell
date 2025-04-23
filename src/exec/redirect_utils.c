#include "../../inc/minishell.h"

int	handle_redirect_l(s_tree *tree)
{
	int	fd;
	char *file;
	
	file = remove_quotes_redirect(tree->right->args[0]);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
	{
		perror("Input redirection failed");
		exit_code(1, 1, 0);
		return (-1);
	}
	return (fd);
}

int	handle_redirect_r(s_tree *tree)
{
	int	fd;
	char *file;
	char *join;
	
	join = join_args(tree->right->args);
	file = strip_quotes_and_join(join);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		exit_code(1, 1, 0);
		return (-1);
	}
	return (fd);
}

int	handle_append(s_tree *tree)
{
	int	fd;

	fd = open(tree->right->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Output redirection failed");
		exit_code(1, 1, 0);
		return (-1);
	}
	return (fd);
}

char	*remove_quotes_redirect(char *str)
{
	char	*new_str;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"') || (str[0] == '\'' && str[len - 1] == '\''))
	{
		new_str = ft_substr(str, 1, len - 2);
		return (new_str);
	}
	return (ft_strdup(str)); // return a copy if no quotes
}

char	*strip_quotes_and_join(char *input)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = safe_malloc(ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] != '"')
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*join_args(char **args)
{
	char	*joined;
	char	*tmp;
	int		i;

	i = 0;
	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while (args[i])
	{
		tmp = safe_malloc(strlen(joined) + strlen(args[i]) + 1);
		tmp[0] = '\0';
		strcat(tmp, joined);
		strcat(tmp, args[i]);
		free(joined);
		joined = tmp;
		i++;
	}
	return (joined);
}