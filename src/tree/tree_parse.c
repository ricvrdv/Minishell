#include "../../inc/minishell.h"

s_tree	*parse_pipe(s_token **tokens)
{
	s_token	*temp;
	s_token	*next_token;
	s_tree	*pipe_node;

	temp = *tokens;
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type == PIPE)
		{
			pipe_node = new_tree_node((*tokens)->next->type);
			(*tokens)->next = NULL;
			pipe_node->left = parse_redirect(&temp);
			pipe_node->right = parse_pipe(&(next_token->next));
			free(next_token->value);
			free(next_token);
			return (pipe_node);
		}
		*tokens = next_token;
	}
	return (parse_redirect(&temp));
}

s_tree	*parse_redirect(s_token **tokens)
{
	s_token	*temp;
	s_token	*next_token;
	s_tree	*redirect_node;

	temp = *tokens;
	if ((*tokens)->type >= REDIRECT_L && (*tokens)->type <= HEREDOC)
		return (redirect_node = especial_node(tokens, temp));
	while (*tokens && (*tokens)->next)
	{
		next_token = (*tokens)->next;
		if ((*tokens)->next->type >= REDIRECT_L
			&& (*tokens)->next->type <= HEREDOC)
		{
			redirect_node = new_tree_node((*tokens)->next->type);
			(*tokens)->next = next_token->next->next;
			redirect_node->left = parse_redirect(&temp);
			redirect_node->right = create_arg_node((next_token->next));
			free(next_token->value);
			free(next_token);
			return (redirect_node);
		}
		*tokens = next_token;
	}
	return (parse_command(&temp));
}

s_tree	*parse_command(s_token **tokens)
{
	s_tree		*command_node;
	int			arg_count;

	command_node = new_tree_node(WORD);
	arg_count = count_arguments(*tokens);
	command_node->args = safe_malloc(sizeof(char *) * (arg_count + 1));
	command_node->argcount = arg_count;
	fill_command_arguments(command_node, tokens, arg_count);
	return (command_node);
}

int	count_arguments(s_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == WORD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	fill_command_arguments(s_tree *command_node,
	s_token **tokens, int arg_count)
{
	int		i;
	s_token	*tmp;

	i = 0;
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->value);
		free(tmp);
		i++;
	}
	command_node->args[arg_count] = NULL;
}
