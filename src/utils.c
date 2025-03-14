#include "../inc/minishell.h"

void	error_exit(char *error)  //used before creating struct
{
	printf(RED"%s\n"RESET, error);
	exit(1);
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

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
		error_exit("Error with Malloc!");
	return (ret);
}

void	free_struct(s_minishell *mini)
{
	
	/*free(mini->full_cmd);*/  //not initialized yet
	free(mini->cur_dir);
	/*clear_token(&mini->tokens);*/  //not initialized yet
	/*clear_env(&mini->env);*/   //not initialized yet
}


void	clear_env(s_env **env)
{
	s_env	*temp = NULL;

	if (!*env)
		return ;
	if(env)
	{
		while (*env)
		{
			temp = (*env)->next;
        	free(*env);
        	*env = temp;
		}
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