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

s_token *new_token(s_type type, char *value)
{
    s_token *token;

    token = safe_malloc(sizeof(s_token));
    if(!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(value);
    if(!token->value)
    {
        free(token);
        return (NULL);
    }
    token->next = NULL;
    return (token);
}


