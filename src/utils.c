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
	
	free(mini->full_cmd);
	free(mini->cur_dir);
	clear_token(&mini->tokens);  //not initialized yet
	clear_env(&mini->env);   //not initialized yet
}


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

void print_tokens(s_minishell *mini)
{
    s_token *current = mini->tokens;
    
    if (!current)
    {
        printf("No tokens found.\n");
        return;
    }
    
    while (current)
    {
        printf("Type: %s, Value: %s\n", current->type, current->value);
        current = current->next;
    }
}

void print_env_list(s_env *env_list)  //for testing
{
    while (env_list)
    {
        printf("%s=%s\n", env_list->key, env_list->value);
        env_list = env_list->next;
    }
}

char    *get_dir()
{
    char *currentdir = NULL;
    currentdir = getcwd(NULL, 1024);
    return currentdir;
}