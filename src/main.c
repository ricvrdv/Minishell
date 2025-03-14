#include "../inc/minishell.h"


int main(int ac, char *av[], char **envp)
{
    s_minishell *mini;
    char *line;
    char buffer[256];
    (void)ac;
    (void)av;
    
    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                        //init values on struc -created-curdir-full_cmd/s_env/s_token
    get_env(mini, envp);                      //iterates env structs / splits and makes new node(linked list) where it puts info
    while((line = readline("> ")) != NULL)    //infinite loop to get input from user
    {
        strncpy(buffer, line, 256);           //copy line to buffer
        buffer[255] = '\0';                   
        add_history(line);
        if(ft_strncmp(buffer, "exit", 4) == 0)
            mini_exit(mini, NULL);
        if(ft_strncmp(buffer, "pwd", 3) == 0)
            printf("%s\n", mini->cur_dir);
        if(ft_strncmp(buffer, "env", 3) == 0)
            print_env_list(mini->env);
    }
    return 0;
}

/*printf("%s\n", buffer);*/ 