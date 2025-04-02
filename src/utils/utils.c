#include "../../inc/minishell.h"

void	error_exit(char *error)
{
	printf(RED"%s\n"RESET, error);
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

void free_struct(s_minishell *mini)
{
    if(mini->cur_dir)
    	free(mini->cur_dir);
    if(mini->env_array)
    	clear_env_array(&mini->env_array);   //todo
    if(mini->env) 
    	clear_env(&mini->env);            //todo
}


char    *get_dir()
{
    char *currentdir;

    currentdir = getcwd(NULL, 1024);
    return currentdir;
}
void	free_stuff(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int space(int c)
{
	return(c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

bool are_counts_odd(int d_count, int s_count)
{
	return(!(d_count % 2) && !(s_count % 2));       //returns true if we have even nbr of quotes on counter
}

int str_size(char *str, char end)                  //will check str_size using end to defined the end
{
	int i;

	i = 0;
	while(*str && str[i] != '\0' && str[i] != end)
		i += 1;
	return (i);
}