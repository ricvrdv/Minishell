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
    if(*line[0] == '\0' || (ft_strncmp(*line, "\n", 2) == 0) || is_space(*line))
    {
        free(*line);
        return (1);
    }
    return 0;
}
