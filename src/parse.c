#include "../inc/minishell.h"

void    start_prompt(s_minishell **mini)
{
    char *line;
    char **buffer;
    int     i;

    while((line = readline("> ")) != NULL)    //infinite loop to get input from user
    {
        i = 0;
        buffer = ft_split(line, ' ');          
        add_history(line);
        if(ft_strncmp(*buffer, "exit", 4) == 0)
            mini_exit(*mini, NULL);
        while(buffer[i])
        {
            get_token(*mini, buffer[i]);
            i++;
        }
        if(ft_strncmp(*buffer, "print", 5) == 0)
            print_tokens(*mini);
        if(ft_strncmp(*buffer, "env", 3) == 0)
            print_env_list((*mini)->env);
        if(ft_strncmp(*buffer, "pwd", 3) == 0)
            ft_printf("%s\n",((*mini)->cur_dir));
        
        free(line);
        i = 0;
        while (buffer[i])
            free(buffer[i++]);
        free(buffer);
    }
    
}

void   get_token(s_minishell *mini, char *str)
{
    char        *value = NULL;
    char        *key = NULL;

    
    if(ft_strncmp(str, "cd", 2) == 0)
    {
        key = "cd";
        value = "cd";
    }
    if(ft_strncmp(str, "pwd", 3) == 0)
    {
        key = "pwd";
        value = "pwd";        
    }
    if(ft_strncmp(str, "|", 1) == 0)
    {
        key = "pipe";
        value = "|";
    }
    if(ft_strncmp(str, "<", 1) == 0)
    {
        key = "redirect_left";
        value = "<";        
    }
    if(ft_strncmp(str, ">", 1) == 0)
    {
        key = "redirect_right";
        value = ">";       
    }
    if(ft_strncmp(str, "&", 1) == 0)
    {
        key = "ampersand";
        value = "&";        
    }
    if(ft_strncmp(str, ";", 1) == 0)
    {
        key = "semicolon";
        value = ";";    
    }
    if(ft_strncmp(str, "(", 1) == 0)
    {
        key = "left_parenthesis";
        value = "(";
            
    }
    if(ft_strncmp(str, ")", 1) == 0)
    {
        key = "right_parenthesis";
        value = ")";        
    }
        if(ft_strncmp(str, "$", 1) == 0)
    {
        key = "dollar_sign";
        value = "$";       
    }
    if(ft_strncmp(str, "/", 1) == 0)
    {
        key = "slash";
        value = "/";    
    }
    if(ft_strncmp(str, "env", 3) == 0)
    {
        key = "envp";
        value = "env";       
    }
    if(key &&  value)
        add_token_node(&(mini->tokens), key, value);
}

