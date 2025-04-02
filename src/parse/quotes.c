#include "../../inc/minishell.h"

void quote_counter(char c, int *s_counter, int *d_counter)    ///check everytime we move the string for single or double quoutes and increments ptr
{
    if(c == '\"')
        (*d_counter)++;
    else if(c == '\'')
        (*s_counter)++;
}


void update_quotes(char c, int *inside, char *quote) {

    if (c == '\'' || c == '\"') {

        if (*inside && c == *quote) {
            *inside = 0; // closing quote
        } else if (!*inside) {
            *inside = 1; // opening quote
            *quote = c;
        }
    }
}
int check_str(char **line)
{
    if(*line[0] == '\0' || 
        ft_strncmp(*line, "\n", 2) == 0 ||
        is_space(*line) ||
        (line[0][0] == '"' && line[0][1] == '"') || 
        (line[0][0] == '\'' && line[0][1] == '\'')) 
        return (1);  //reach continue and restart loop
    return 0; // No errors
}


int empty_quotes(const char *str) 
{
    char quote;
    int has_non_space;
    int i;

    i = 0;
    while(str[i++])
    {
        if(str[i] >= 65 && str[i] <= 122)
            return 0;
    }
    i = 0;
    while (*str) 
    {
        if (*str == '"' || *str == '\'') 
        {  
            quote = *str++;  // Store quote type
            has_non_space = 0;
            if (*str == quote)
                return 0;
            while (*str && *str != quote) 
            {  
                if (*str != ' ') 
                    has_non_space = 1;
                str++;
            }
            if (*str == quote) 
            {  
                if (has_non_space) 
                    return 0;  // Found text inside quotes
                else 
                {
                    printf(" : Command not found\n");
                    return 1;  // Only spaces inside quotes
                }
            }
        }
        str++;
    }
    return 0;  // No non-space characters found inside quotes
}