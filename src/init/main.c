#include "../../inc/minishell.h"


int main(int ac, char *av[], char **envp)
{
    s_minishell *mini;
    (void)ac;
    (void)av;
    
    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                        //init values on struc -created-curdir-full_cmd/s_env/s_token
    get_env(mini, envp);                      //iterates env structs / splits and makes new node(linked list) where it puts info
    start_prompt(&mini);                       //asks user for input in infinite loop 
    return 0;
}

void    start_prompt(s_minishell **mini)
{
    char    *line;
    s_token *tokens;
    (void)mini;
    while(1)    //infinite loop to get input from user
    {
        line = readline(">");
        if(!line)
            break;       
        if(check_str(&line))
            continue;   //if returns 1 skips and start loop again.
        add_history(line);
        tokens = make_token(&line, &tokens); //parse str //has unclose quotes? / has invalid redirections /    //parse tokens
        //if tokens ok make tree
        //update env()
        if(ft_strncmp(line, "token", 5) == 0)
            print_token_list(tokens);
        if(ft_strncmp(line, "exit", 4) == 0)  //just to be able to exit
            mini_exit(*mini, NULL);
        free(line);                         //avoid leaks atm
    }
    
}

int check_str(char **line)
{
    if(*line[0] == '\0' || ft_strncmp(*line, "\n", 2) == 0|| is_space(*line)) //if empty line /only contains spaces/only contains \n
    {
        free(*line);
        return (1);  //reach continue and restart loop
    }
    return (0);
}

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
        if (!ft_strchr(str, '>' ) && !ft_strchr(str, '<') && !ft_strchr(str, '|'))       //if we find a operator use handle signs
            handle_word(&str, &tokens);
        /*else                            //else we have text handle word
            handle_word(&str, &tokens);*/
        str++;
    }
    return (tokens);
}

void    handle_word(char **str, s_token **tokens)
{
    char *start;
    s_token *new_tok;

    start = *str;
    new_tok = new_token(TOKEN);
    new_tok->value = ft_substr(start, 0, *str - start);

    add_token_node(tokens, new_tok);
}

void print_token_list(s_token *token_list)  //for testing
{
    while (token_list)
    {
        printf("%s\n", token_list->value);
        token_list = token_list->next;
    }
}