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
        if(tree)
        {
            execute_node(tree, *mini, STDIN_FILENO, STDOUT_FILENO);  //use nodes from tree, acess env from mini
        }
        free(line);
    }
}

void exec_tree(s_tree *tree)                            //add later *mini to get env
{
    int pipes[12];                                        // pipes[0] = | / pipes[1] = > / pipes[2] = >> / pipes[3] = < / pipes[4] = <<
    //int flag;

    init_pipes(pipes, 1);                                  //set pipes[0->5 to 0]
    count_pipes_redir(tree, pipes);                     //increment nbr of pipes or redirects
    init_pipes(pipes, 0);                                //check for nbr of pipes and puts on pipes[0] set flag to ready pipe[11]
    rename_nodes(tree);                                 //rename nodes to make it easier
    //expand check 
    //check_file permission

}

void    count_pipes_redir(s_tree *tree, int *pipes)
{
    tree->file_type = 0;
    if(tree->type == PIPE)
        pipes[5] += 1;                                            //counter nbr or pipes
    else if(tree->type == REDIRECT_R || tree->type == APPEND)
        pipes[4] += 1;                                             //counter for  > and >>
    else if(tree->type == REDIRECT_L  || tree->type == HEREDOC)
        pipes[3]++;                                                //counter for < and <<
    if(tree->left)
        count_pipes_redir(tree->left, pipes);
    if(tree->right)
        count_pipes_redir(tree->right, pipes);
}

void init_pipes(int *pipes, int flag)
{
    int i;

    i = 0;
    if(flag)                 //to set all to null
        while(i < 12)
            pipes[i++] = 0;
    else if(pipes[5])       //on second call put nbr of pipes on pipe[0]
        pipes[0] = pipes[0] + 1;
    pipes[11] = 1;          //flag ready;
}

void rename_nodes(s_tree *tree)
{
    if(tree->type != CMD)          //If we have a pipe or redirect node
    {
        tree->file_type = TREE_READY;
        if(tree->type == REDIRECT_R && tree->right)      //if we have > node and something on ride side (file to write)
            tree->right->file_type == WRITE_FILE;
        if(tree->type == APPEND && tree->right)          // >> Append node
            tree->right->file_type == WRITE_APPEND_FILE;
        if(tree->type == REDIRECT_L && tree->right)      //Read file R_l node <
            tree->right->file_type == READ_FILE;
        if(tree->type == HEREDOC && tree->right)         //Heredoc node
            tree->right->file_type == HEREDOC_FILE;
        if(tree->type == PIPE)
        {
            if(tree->right)
                tree->right->file_type = CMD_READY;
            if(tree->left)
                tree->left->file_type = CMD_READY;
        }
    }
    if(!tree->file_type)
        tree->file_type = CMD_READY;
    if(tree->left)
        rename_nodes(tree->left);
    if(tree->right)
        rename_nodes(tree->right);
}
