#include "../../inc/minishell.h"

void    start_prompt(s_minishell **mini)
{
    char    *line;
    s_token *tokens;
    s_tree  *tree;
    (void)mini;
    while(1)   
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
            printf(" : Command %d not found\n", line[0]);
            continue;   //if returns 1 skips and start loop again.
        }
        if(ft_strlen(line) > 0)
            add_history(line);                                              
        tokens = make_token(&line, &tokens); //parse str //has unclose quotes? / has invalid redirections /    //parse tokens
        tree = parse_token(&tokens);  //check if tokens exist // if it does enteres parse_pipe and parse_redirect
        ft_print_tree(tree, 0);      //only to be able to check . atm tree seems decent .
        /*
        if(tree)
        parsetree(tree) will iterate linked list and execute what comes first 
        */
        free(line);
    }
}