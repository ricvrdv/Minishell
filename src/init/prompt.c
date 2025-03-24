#include "../../inc/minishell.h"

void    start_prompt(s_minishell **mini)
{
    char    *line;
    s_token *tokens;
    (void)mini;
    while(1)    //infinite loop to get input from user
    {
        line = readline(">");
        if (line == NULL) 
        {
            printf("exiting...\n");
            mini_exit(*mini, NULL); // Call mini_exit to clean up
            break; // Exit the loop
        }      
        if(check_str(&line) || empty_quotes(line))
        {
            free(line);
            printf("Empty command. Please enter a valid command\n");
            continue;   //if returns 1 skips and start loop again.
        }
        if(ft_strlen(line) > 0)
            add_history(line);
        tokens = make_token(&line, &tokens); //parse str //has unclose quotes? / has invalid redirections /    //parse tokens 
        if(tokens)
        {
            print_token(tokens);
            clear_token(&tokens);
            print_token(tokens);
        }
        free(line);                         
    }
    
}