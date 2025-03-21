#include "../../inc/minishell.h"


const char *token_name(s_type type)
{
    const char  *token_type[7];

    token_type[0] = "PIPE";
    token_type[1] = "REDIRECT_L";
    token_type[2] = "REDIRECT_R";
    token_type[3] = "WORD";
    token_type[4] = "TOKEN";
    token_type[5] = "APPEND";
    token_type[6] = "HEREDOC";
    if(type >= 0 && type < 7)
        return (token_type[type]);
    return ("DUNNO");
}

void print_token(s_token *tokens)
{
    s_token *token;
    int i = 1;

    token = tokens;
    while(token)
    {
        printf("Token %i: %s\n",i ,token->value);
        printf("Type: %s\n", token_name(token->type));
		printf("--------------------------------------------------\n");
 		token = token->next;
        i++;
    }
}

void print_token_list(s_token *token_list)
{
    while (token_list)
    {
        if (token_list->value && *token_list->value)  
            printf("Token: [%s]\n", token_list->value);
        token_list = token_list->next;
    }
}