#include "../../inc/minishell.h"

void prep_tree(s_tree *tree, s_minishell *mini, int *status)                            //add later *mini to get env
{
    int counter[12];                                                             // pipes[0] = | / pipes[1] = > / pipes[2] = >> / pipes[3] = < / pipes[4] = <<
    
    rename_nodes(tree);                                                     //rename nodes to make it easier
    init_pipes_array(counter, 1);                                           //set pipes[0->12 to 0]
    init_pipes_array(counter, 0);                     //check for nbr of pipes and puts on pipes[0]
    count_pipes_redir(tree, counter);           //increment nbr of pipes or redirects
    expand_tree(mini, tree);
    *status = execute_node(tree, mini, STDIN_FILENO, STDOUT_FILENO);

}

void    count_pipes_redir(s_tree *tree, int *counter) 
{
    tree->file_type = 0;
    if(tree->type == PIPE)
        counter[5] += 1;                                    //counter nbr or pipes
    else if(tree->type == REDIRECT_R || tree->type == APPEND)
        counter[4] += 1;                          //counter for  > and >>
    else if(tree->type == REDIRECT_L  || tree->type == HEREDOC)
        counter[3]++;                                     //counter for < and <<
    if(tree->left)
        count_pipes_redir(tree->left, counter);
    if(tree->right)
        count_pipes_redir(tree->right, counter);
}

void init_pipes_array(int *counter, int flag)
{
    int i;

    i = 0;
    if(flag)                 //to set all to null
        while(i < 12)
            counter[i++] = 0;
    else if(counter[5])       //on second call put nbr of pipes on pipe[0]  
        counter[0] = counter[0] + 1;
}

void rename_nodes(s_tree *tree)
{
    if(tree->type != WORD)          //If we have a pipe or redirect node
    {
        tree->file_type = TREE_READY;                    // 100
        if(tree->type == REDIRECT_R && tree->right)      //if we have > node and something on ride side (file to write)
            tree->right->file_type = WRITE_FILE;            // 200
        if(tree->type == APPEND && tree->right)          // >> Append node
            tree->right->file_type = APPEND_FILE;           //300
        if(tree->type == REDIRECT_L && tree->right)      //Read file R_l node <
            tree->right->file_type = READ_FILE;             //400
        if(tree->type == HEREDOC && tree->right)         //Heredoc node
            tree->right->file_type = HEREDOC_FILE;          //500
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
 