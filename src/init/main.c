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
    s_token *tokens;
    char **buffer;
    (void)mini;
    while(1)    //infinite loop to get input from user
    {
        line = readline(">");
        if(!line)
            break;       
        if(check_str(&line))
            continue;   //if returns 1 skips and start loop again.
        add_history(line);
        buffer = ft_split(line, ' ');
        tokens = make_token(&line, &tokens); //parse str //has unclose quotes? / has invalid redirections /    //parse tokens 
        if(tokens)
        {
            while(tokens)
            {
                if(ft_strncmp(*buffer, "cd", 2) == 0)
                    mini_cd(*mini, buffer);
                else if(ft_strncmp(*buffer, "env", 3) == 0)
                    mini_env((*mini)->env_array);
                else 
                {
                    if (fork() == 0)
                        execute_command(*mini, buffer);
                    wait(NULL);
                }
                print_token_list(tokens);
                clear_token(&tokens);
                print_token_list(tokens);
            }
        }
        /*printf("curdir : %s\n", (*mini)->cur_dir);*/
        //if tokens ok make tree
        //update env()
        free(line);                         //avoid leaks atm */
    }
    
}

int check_str(char **line)
{
    if(*line[0] == '\0' || ft_strncmp(*line, "\n", 2) == 0|| is_space(*line)) //if empty line /only contains spaces/only contains \n
    {
        free(*line);  //safety?
        return (1);  //reach continue and restart loop
    }
    return (0);
}

void print_token_list(s_token *token_list)
{
    while (token_list)
    {
        if (token_list->value && *token_list->value)  
            printf("Token: [%s]\n", token_list->value);
        token_list = token_list->next;
    }
}


