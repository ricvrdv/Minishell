#include "minishell.h"

int is_nbr(char *str)
{
    int i = 0;
    int token = 0;
    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
            token++;
        i++;
    }
    return token;
}
int is_char(char *str)
{
    int i = 0;
    int token = 0;
    while(str[i])
    {
        if(str[i] >= 65 && str[i] <= 122)
            token++;
        i++;
    }
    return token; 
}
int is_pipe(char *str)
{
    int i = 0;
    int token = 0;
    while(str[i])
    {
        if(str[i] == 124)
            token++;
        i++;
    }
    return token; 
}