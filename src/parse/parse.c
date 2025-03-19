#include "../../inc/minishell.h"

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

int full_check(char *str)
{
    if(check_doubles(str))
    {
        ft_putstr_fd("Logical opertators are not suported.\n", 2);
        return (1);
    }
    if(check_pipe(str))
    {
        ft_putstr_fd("Misplaced operator.\n", 2);
        return (1);
    }
    if(check_quotes(str))
    {
        ft_putstr_fd("Unclosed quote.\n", 2);
        return (1);
    }
    if(check_redirect(str))
    {
        ft_putstr_fd("Invalid redirect.\n", 2);
        return (1);
    }
    return (0);     // all good with the str
}


int check_doubles(char *str)   //checks for && or ||
{
    while(*str)
    {
        if((*str == '&' && *(str + 1) == '&') || (*str == '|' && *(str + 1) == '|'))
            return (1);
        str++;
    }
    return (0);
}   

int check_redirect(char *str)
{
    while(*str)
    {
        if(*str == '<' || *str == '>')
        {
            if(invalid_operator(&str))
                return (1);
        }
        else
            str++;
    }
    return (0);
}

int check_pipe(char *str)
{
    int flag;                      // tracker to check if pipe already used and now expecting cmd not another pipe

    flag = 0;
    while(*str)
    {
        if(*str == '|')
        {
            if(flag)
                return(1);       //expecting a cmd
            flag = 1;
        }
        else if(!space(*str))  //is there is more txt after space
            flag = 0;              //found another cmd can use another pipe after
        str++;  
    }
    if(flag)                        //positive flag means we still miss a cmd (exemple : cdm | )
        return (1);
    return (0);
}