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

