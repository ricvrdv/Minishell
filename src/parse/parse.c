#include "../../inc/minishell.h"

int full_check(char *str)
{
    char *temp;

    temp = ft_strtrim(str, " \t\n\v\f\r");
    if(check_doubles(temp))
    {
        ft_putstr_fd("Logical opertators are not suported.\n", 2);
        return (1);
    }
    if(check_pipe(temp))
    {
        ft_putstr_fd("Misplaced operator.\n", 2);
        return (1);
    }
    if(check_quotes(temp))
    {
        ft_putstr_fd("Unclosed quote.\n", 2);
        return (1);
    }
    if(check_redirect(temp))
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
    while(*str && *str == ' ')     //skip spaces
        str++;
    if(*str == '|')
        return 1;
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

int     check_quotes(char *str)
{
    char type;

    type = 0;
    while(*str)
    {
        if(*str == '\'' || *str == '\"')
        {
            if(type == *str)
                type = 0;
            else if(!type)
                type = *str;
        }
        str++;
    }
    return (type != 0);
}

