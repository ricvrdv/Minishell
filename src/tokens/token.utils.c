#include "../../inc/minishell.h"


s_token *make_token(char *str, s_token **tokens)
{
    char *trim;

    trim = ft_strtrim(str, " \t\n\v\f\r");
    free(str);
    if(full_check(trim))
    {
        free(trim);
        return NULL;
    }
    *tokens = get_token(trim);
    free(trim);
    return (*tokens);
}

s_token     *get_token(char *str)
{
    s_token  *tokens;

    tokens = NULL;
    while(*str)
    {
        while(*str && ft_strchr(" \t\n", *str))
            str++;
        if (*str == '>' || *str == '<' || *str == '|')       //if we find a operator use handle signs
            handle_sign(&str, &tokens);
        else                        //else we have text handle word
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


