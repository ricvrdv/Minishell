#include "../../inc/minishell.h"

void quote_counter(char c, int *s_counter, int *d_counter)    ///check everytime we move the string for single or double quoutes and increments ptr
{
    if(c == '\"')
        (*d_counter)++;
    else if(c == '\'')
        (*s_counter)++;
}


void    update_quotes(char c, int *inside, char *quote)
{
    if(c == '\'' || c == '\"')
    {
        *inside = 1;                ///we are inside quotes ' ""
        *quote = c;
    }
    if(*inside && c == *quote) //we found the closing quote
        *inside = 0;
}