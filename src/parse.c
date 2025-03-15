#include "../inc/minishell.h"

void    start_prompt(s_minishell **mini)
{
    char *line;
    char buffer[256];

    while((line = readline("> ")) != NULL)    //infinite loop to get input from user
    {

        strncpy(buffer, line, 256);           //copy line to buffer
        buffer[255] = '\0';          
        add_history(line);
        if(ft_strncmp(buffer, "exit", 4) == 0)
            mini_exit(*mini, NULL);
        get_token(*mini, buffer);
        if(ft_strncmp(buffer, "print", 5) == 0)
            print_tokens(*mini);
        free(line);
    }
    
}

void   get_token(s_minishell *mini, char *str)
{
    char        *value;
    char        *key;

    while(*str)
    {
        if(ft_strncmp(str, "cd", 2) == 0)
        {
            key = "cd";
            value = "cd";
            add_token_node(&(mini->tokens), key, value);
        }
        if(ft_strncmp(str, "pwd", 3) == 0)
        {
            key = "pwd";
            value = "pwd";
            add_token_node(&(mini->tokens), key, value);
        }
        if(ft_strncmp(str, "|", 1) == 0)
        {
            key = "pipe";
            value = "|";
            add_token_node(&(mini->tokens), key, value);
        }
        str++;
    }
}