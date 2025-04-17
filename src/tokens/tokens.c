#include "../../inc/minishell.h"

void	handle_word(char **str, s_token **tokens)
{
	char	*start;
	char	quote;
	int		inside;

	start = *str;
	quote = 0;
	inside = 0;
	while (**str)
	{
		update_quotes(**str, &inside, &quote);
		if (inside == 0 && ft_strchr(" \t\n><|", **str))
			break ;
		(*str)++;
	}
	put_word(&start, str, tokens);
}

void	handle_sign(char **str, s_token **tokens)
{
	if (**str == '>')
	{
		if ((*str)[1] == '>')
		{
			add_token_node(tokens, new_token(APPEND, ">>"));
			(*str)++;
		}
		else
			add_token_node(tokens, new_token(REDIRECT_R, ">"));
	}
	else if (**str == '<')
	{
		if ((*str)[1] == '<')
		{
			add_token_node(tokens, new_token(HEREDOC, "<<"));
			(*str)++;
		}
		else
			add_token_node(tokens, new_token(REDIRECT_L, "<"));
	}
	else if (**str == '|')
		add_token_node(tokens, new_token(PIPE, "|"));
	(*str)++;
}

void	put_word(char **start, char **end, s_token **tokens)
{
	char	*input;

	if (*end > *start)
	{
		input = ft_strndup(*start, *end - *start);
		if (input)
		{
			add_token_node(tokens, new_token(WORD, input));
			free(input);
		}
	}
}
