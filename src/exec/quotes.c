#include "../../inc/minishell.h"

void remove_quotes(char *arg) 
{
    int len;
    //int quote_count;
    
    leading_quotes(arg);                                            //skips ""before cmd
    //quote_count = count_quotes(arg);                                //counts nbr of quotes
    len = ft_strlen(arg);                                           //len of arg
    if (len > 1 && arg[0] == '\'' && arg[len - 1] == '\'')          //atm removes quotes from tokens
    {
        arg[len - 1] = '\0';
        ft_memmove(arg, arg + 1, len - 1);
    }
    else if (len > 1 && arg[0] == '"' && arg[len - 1] == '"')       //same thing
    {
        arg[len - 1] = '\0';
        ft_memmove(arg, arg + 1, len - 1);
    }
    remove_trailing(arg);                                            //remove trailing quote echo "hello"""
}

void remove_trailing(char *arg)
{
    int len;

    len = ft_strlen(arg);
    while (len > 0 && arg[len - 1] == '"') 
    {
        arg[len - 1] = '\0';                                        // Remove trailing quote
        len--;                                                      // Update length
    }

}

void leading_quotes(char *str)
{
    int len; 
    
    len = ft_strlen(str);
    while (len > 1 && str[0] == '"' && str[1] == '"') 
    {
        ft_memmove(str, str + 2, len - 1); // Move the string left by 2
        str[len - 2] = '\0'; // Null-terminate the new string
        len -= 2; // Update the length
    }
    
}

int count_quotes(const char *str)
{
    int counter;
    int len;
    int i;

    i = 0;
    counter = 0;
    len = ft_strlen(str);
    while(i < len)
    {
        if(str[i] == '"')
            counter++;
        i++;
    }
    return counter;
}

void clean_args(char **args, int arg_count)
{
    int index;

    index = 0;
    while(index < arg_count)
    {
        remove_quotes(args[index]);
        index++;
    }
}