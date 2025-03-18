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
          while(buffer[i])
        {
            get_token(*mini, buffer[i]);
            i++;
        }
        if(ft_strncmp(*buffer, "exit", 4) == 0)
            mini_exit(*mini, NULL);
        else if(ft_strncmp(*buffer, "print", 5) == 0)
        {
            print_tokens(*mini);
            print_args(*mini);
        }
        else
            ft_cmd(*mini, buffer[0], NULL);
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

    check_cmds(str, &key, &value);
    check_signs(str, &key, &value);
    check_redirect(str, &key, &value);
    if(key &&  value)
        add_token_node(&(mini->tokens), key, value);
    else
    {
        key = ft_strdup(str);
        add_args_node(&(mini->args), key);
        free(value);
    }
}

void    check_cmds(char *str, char **key, char **value)
{
    if(ft_strncmp(str, "cd", 2) == 0)
    {
        *key = "cd";
        *value = "cd";
    }
    if(ft_strncmp(str, "pwd", 3) == 0)
    {
        *key = "pwd";
        *value = "pwd";        
    }
    if(ft_strncmp(str, "echo", 4) == 0)
    {
        *key = "echo";
        *value = "echo";        
    }
    if(ft_strncmp(str, "env", 3) == 0)
    {
        *key = "env";
        *value = "envp";        
    }
    if(ft_strncmp(str, "export", 6) == 0)
    {
        *key = "export";
        *value = "export";        
    }
    if(ft_strncmp(str, "unset", 5) == 0)
    {
        *key = "unset";
        *value = "unset";        
    }

}
void    check_signs(char *str, char **key, char **value)
{
    if(ft_strncmp(str, "&", 1) == 0)
    {
        *key = "ampersand";
        *value = "&";        
    }
    if(ft_strncmp(str, ";", 1) == 0)
    {
        *key = "semicolon";
        *value = ";";    
    }
    if(ft_strncmp(str, "$", 1) == 0)
    {
        *key = "dollar_sign";
        *value = "$";       
    }
    if(ft_strncmp(str, "/", 1) == 0)
    {
        *key = "slash";
        *value = "/";    
    }
}
void    check_redirect(char *str, char **key, char **value)
{
  
    if(ft_strncmp(str, "<", 1) == 0)
    {
        *key = "redirect_left";
        *value = "<";        
    }
    if(ft_strncmp(str, ">", 1) == 0)
    {
        *key = "redirect_right";
        *value = ">";       
    }
    if(ft_strncmp(str, "|", 1) == 0)
    {
        *key = "pipe";
        *value = "|";
    }
}
 /*if(ft_strncmp(*buffer, "env", 3) == 0)
            print_env_list((*mini)->env);
        if(ft_strncmp(*buffer, "pwd", 3) == 0)
            ft_printf("%s\n",((*mini)->cur_dir));*/