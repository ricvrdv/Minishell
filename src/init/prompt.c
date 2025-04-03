#include "../../inc/minishell.h"

void        start_prompt(s_minishell **mini)
{
    char    *line;
    s_token *tokens;
    s_tree  *tree;

    (void)mini;
    while(1)   
    {
        line = readline(">");
        if (line == NULL)
            break; // Exit the loop
        if(check_str(&line) || empty_quotes(line))
            continue;   //if returns 1 skips and start loop again.
        add_history(line);                                              
        tokens = make_token(&line, &tokens); 
        if(tokens)
        {
            tree = parse_token(&tokens);  
            prep_tree(tree, *mini); 
            //todo 
            //exec_cmd
            //clear tokens / tree            
        }
        free(line);
    }
}