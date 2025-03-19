#include "../../inc/minishell.h"

char    *s_spaces(char *str)
{
    while(*str && (*str == ' ' || *str == '\t'))
        str++;
    return (str);
}

int invalid_operator(char **str)   //starts at > or <
{
    char    *start;

    start = *str;           //start = < or >
    (*str)++;               //ptr str moved to next char
    if(*start == **str)     //if >> or << iterate
        (*str)++;
    *str = s_spaces(*str);  //skip spaces
    if(**str == '\0' || **str == '>' || **str == '|' || **str == '<')
        return (1);         //if eof or redirect or pipe (ls > , cat <  < file , | ls or ls |)
    return (0);
}

int is_space(char *str)
{
    int i;

    i = 0;
    while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i = i + 1;
    if(str[i] == '\0')
        return (1);    //if only spaces in string returns 1
    return (0);         //else if has spaces but then something else returns 0
}

int invalid_position(char **str)
{
    char    *start;

    start = *str;    //begining of string 
    (*str)++;
    if(*start == **str)
        (*str)++;
    *str = jump_spaces(*str);
    if(**str == '\0' || **str == '>' || **str == '<' || **str == '|')
        return (1);   //if we find one of these before anything else return 1 (invalid position of sign)
    return (0);       //else we are fine
}

char *jump_spaces(char *str)
{
    while(*str && (*str == ' ' || *str == '\t'))
        str++;
    return (str);
}

