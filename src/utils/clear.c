#include "../../inc/minishell.h"

void	clear_env(s_env **env)
{
	s_env	*temp;

	temp = NULL;
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
	s_token	*temp;

	temp = NULL;
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

void	clear_tree(s_tree **tree)
{
	int i;
	if(!tree || !*tree) // Base case to stop recursion
		return;
	clear_tree(&(*tree)->left);
	clear_tree(&(*tree)->right);
	if ((*tree)->args)
	{
		i = 0;
		while ((*tree)->args[i])
		{
			free((*tree)->args[i]);
			i++;
		}
		free((*tree)->args);
	}
	free(*tree);
	*tree = NULL;
}

void	clear_env_array(char ***env_array)
{
	int	i;

	i = 0;
	while ((*env_array)[i])
	{
		free((*env_array)[i]);
		i++;
	}
	free(*env_array);
	*env_array = NULL;
}


void mini_exit(s_minishell *mini, char *error)
{
    if (mini->created)
        free_struct(mini);  
    if (error)
        printf(RED "%s\n" RESET, error);  // Print any error message
    clear_history();  // Clear history, if applicable
    free(mini);  // Finally, free the struct itself
    exit(1);  // Exit with status 1 (indicating an error)
}