#include "../../inc/minishell.h"

void	start_prompt(s_minishell **mini)
{
	char	*line;
	s_token	*tokens;
	s_tree	*tree;
	int		status;

	(void)mini;
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if (check_str(&line))
			continue ;
		add_history(line);
		tokens = make_token(line, &tokens);
		if (tokens)
		{
			tree = parse_token(&tokens);
			prep_tree(tree, *mini, &status);
			clear_tree(&tree);
		}
	}
}
