#include "../../inc/minishell.h"

void	add_env_node(s_env **env_list, char *key, char *value)
{
	s_env	*new_node;

	new_node = safe_malloc(sizeof(s_env));
	new_node->key = key;
	new_node->value = value;
	new_node->next = *env_list;
	*env_list = new_node;
}

void	add_token_node(s_token **tokens, s_token *new_token)
{
	s_token	*last;

	if (!new_token)
		return ;
	if (!*tokens)
		*tokens = new_token;
	else
	{
		last = *tokens;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}
