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
    char    *start;
    char    quote;
    int     inside;                 //if inside a quote = 1 else = 0

    start = *str;
    quote = 0;
    inside = 0;
    while(**str)
    {
        update_quotes(**str, &inside, &quote);
        if(inside == 0 && ft_strchr(" \t\n><|", **str))     //if not inside quotes and found operator, space or eof 
            break;                                          //leave loop . put token
        (*str)++;
    }
    put_word(&start, str, tokens);                        //str is has end of word

}

void    handle_sign(char **str, s_token **tokens)
{
    if(**str == '>')
    {
        if ((*str)[1] == '>')
        {
            add_token_node(tokens, new_token(APPEND, ">>"));                //tokens the struct where we put , new token makes new node there
            (*str)++;                                                       //to skip extra sign
        }
        else
            add_token_node(tokens, new_token(REDIRECT_R, ">"));
    }
    else if(**str == '<')
    {
        if ((*str)[1] == '<')
        {
            add_token_node(tokens, new_token(HEREDOC, "<<"));
            (*str)++;
        }
        else
            add_token_node(tokens, new_token(REDIRECT_L, "<"));
    }
    else if(**str == '|')
        add_token_node(tokens,new_token(PIPE, "|"));     
    (*str)++;
}

void    put_word(char **start, char **end, s_token **tokens)
{
    char    *input;

    if(*end > *start)
    {
       input = ft_strndup(*start, *end - *start);        //allocate memory for end - start = len;
       if(input)
       {
            add_token_node(tokens, new_token(WORD, input));
            free(input);
       }
    }
}

