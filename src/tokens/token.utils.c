#include "../../inc/minishell.h"

s_token     *make_token(char **str, s_token **tokens)
{

    if(full_check(*str))         //will check for doubles/quotes/pipes/redirects
    {
        return NULL; 
    }
    *tokens = get_token(*str);   //will check for operators or text and put tokens in struct 
    return (*tokens);
}

s_token     *get_token(char *str)
{
    s_token  *tokens;

    tokens = NULL;
    while(*str)
    {
        if(*str == ' ')  //skip spaces
            str++;
        if (*str == '>' || *str == '<' || *str == '|')       //if we find a operator use handle signs
            handle_sign(&str, &tokens);
        else if(*str)                       //else we have text handle word
            handle_word(&str, &tokens);
    }
    return (tokens);
}

void    handle_word(char **str, s_token **tokens)
{
    char *start;
    s_token *new_tok;
    int len;

    len = 0;
    while(**str == ' ' || **str == '\t')                                                          
        (*str)++;
    start = *str;
    while (**str && **str != ' ')                // Read till space
    {
        (*str)++;  
        len++;                                   //len is equal to end of word 
    }
    new_tok = new_token(TOKEN);                  //allocates space and starts the struct
    new_tok->value = ft_substr(start, 0, len);   //assign value = substring = full word
    if(len > 0)                                  //only make token if there is something. avoid token spaces
    {
        new_tok = new_token(TOKEN);
        new_tok->value = ft_substr(start, 0, len);
        add_token_node(tokens, new_tok);
    }
}

void    handle_sign(char **str, s_token **tokens)
{
    s_token *new_tok;
    int len;

    len = 1;
    if ((*str)[1] == '>' || (*str)[1] == '<') // Handle ">>" or "<<"  heredoc
        len = 2;                                // if we find >> len 2 to make sure to substr correctly
    new_tok = new_token(OPERATOR);
    new_tok->value = ft_substr(*str, 0, len);
    add_token_node(tokens, new_tok);
    *str += len;
}
