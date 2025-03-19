#include "../../inc/minishell.h"


int main(int ac, char *av[], char **envp)
{
    s_minishell *mini;
    (void)ac;
    (void)av;
    
    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                        //init values on struc -created-curdir-full_cmd/s_env/s_token
    get_env(mini, envp);                      //iterates env structs / splits and makes new node(linked list) where it puts info
    start_prompt(&mini);                       //asks user for input in infinite loop 
    return 0;
}

void    start_prompt(s_minishell **mini)
{
    char    *line;
    (void)mini;
    while(1)    //infinite loop to get input from user
    {
        line = readline(">");
        if(!line)
            break;       
        if(check_str(&line))
            continue;   //if returns 1 skips and start loop again.
        add_history(line);
        full_check(line);  //parse str //has unclose quotes? / has invalid redirections /  
        //parse tokens
        //if tokens ok make tree
        //update env()
        if(ft_strncmp(line, "exit", 4) == 0)  //just to be able to exit
            mini_exit(*mini, NULL);
        free(line);                         //avoid leaks atm
    }
    
}

int check_str(char **line)
{
    if(*line[0] == '\0' || ft_strncmp(*line, "\n", 2) == 0|| is_space(*line)) //if empty line /only contains spaces/only contains \n
    {
        free(*line);
        return (1);  //reach continue and restart loop
    }
    return (0);
}
