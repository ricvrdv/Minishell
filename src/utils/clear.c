#include "../../inc/minishell.h"

void	clear_env(s_env **env)
{
	s_env	*temp = NULL;

	if (!*env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->key);
       	free((*env)->value);
		free(*env);
    	*env = temp;
	}
}

void	clear_token(s_token **token)
{
	s_token	*temp = NULL;

	if (!*token)
		return ;
	if(token)
	{
		while (*token)
		{
			temp = (*token)->next;
        	free(*token);
        	*token = temp;
		}
	}
}

void	mini_exit(s_minishell *mini, char *error)
{
	if(mini->created)
		free_struct(&(*mini));
	if(error)
		printf(RED"%s\n"RESET, error);
	clear_history();
	free(mini);
	exit(1);
}