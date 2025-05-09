/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:56:27 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/09 12:46:34 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
