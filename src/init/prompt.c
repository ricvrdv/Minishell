#include "../../inc/minishell.h"

void    start_prompt(s_minishell **mini)
{
    char    *line;
    s_token *tokens;
    s_tree  *tree;
    int     flag;

    (void)mini;
    while(1)   
    {
        flag = 0;
        line = readline(">");
        if (line == NULL)
            break; // Exit the loop
        if(check_str(&line) || empty_quotes(line))
            continue;   //if returns 1 skips and start loop again.
        add_history(line);                                              
        tokens = make_token(&line, &tokens); 
        if(!tokens)
            flag = 1;
        if(!flag)
        {
            tree = parse_token(&tokens);  
            prep_tree(tree);             
        }
        free(line);
    }
}




