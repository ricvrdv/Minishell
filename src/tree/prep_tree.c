#include "../../inc/minishell.h"

void prep_tree(s_tree *tree)                            //add later *mini to get env
{
    int pipes[12];                                        // pipes[0] = | / pipes[1] = > / pipes[2] = >> / pipes[3] = < / pipes[4] = <<
    //int flag;

    //flag = 0;
    init_pipes_array(pipes, 1);                          //set pipes[0->12 to 0]
    count_pipes_redir(tree, pipes);                      //increment nbr of pipes or redirects
    init_pipes_array(pipes, 0);                                //check for nbr of pipes and puts on pipes[0]
    rename_nodes(tree);                                 //rename nodes to make it easier
    print_tree_status(pipes, tree);
    //check_file permission                             //for > >> < << on our cmds (cd , echo)  
    //expand check 
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

void init_pipes_array(int *pipes, int flag)
{
    int i;

    i = 0;
    if(flag)                 //to set all to null
        while(i < 12)
            pipes[i++] = 0;
    else if(pipes[5])       //on second call put nbr of pipes on pipe[0]  
        pipes[0] = pipes[0] + 1;
}

void rename_nodes(s_tree *tree)
{
    if(tree->type != CMD)          //If we have a pipe or redirect node
    {
        tree->file_type = TREE_READY;
        if(tree->type == REDIRECT_R && tree->right)      //if we have > node and something on ride side (file to write)
            tree->right->file_type = WRITE_FILE;
        if(tree->type == APPEND && tree->right)          // >> Append node
            tree->right->file_type = APPEND_FILE;
        if(tree->type == REDIRECT_L && tree->right)      //Read file R_l node <
            tree->right->file_type = READ_FILE;
        if(tree->type == HEREDOC && tree->right)         //Heredoc node
            tree->right->file_type = HEREDOC_FILE;
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
void print_tree_status(int *pipes, s_tree *tree)
{
    printf("status of main node : %d\n", tree->file_type);
    if(pipes[5])
    printf("nbr of pipes : %d\n", pipes[5]);
    if(pipes[4])
    printf("nbr of > or >> : %d\n", pipes[4]);
    if(pipes[3])
    printf("nbr of < or << : %d\n", pipes[3]);
}
 
int check_cmd(char *cmd)        ///will check if cmd is built in or not  // its working
{
    char *temp;
    int   flag;
    size_t   len;
    
    flag = 0;
    len = ft_strlen(cmd);
    temp = safe_malloc(len + 1);

    ft_strlcpy(temp, cmd, len + 1);
    if(ft_strncmp(temp, "cd", 2) == 0
        || ft_strncmp(temp, "echo", 4) == 0
        || ft_strncmp(temp, "pwd", 3) == 0
        || ft_strncmp(temp, "export", 6) == 0
        || ft_strncmp(temp, "unset", 5) == 0
        || ft_strncmp(temp, "env", 3) == 0
        || ft_strncmp(temp, "exit", 4) == 0)
        flag = 1;                                      //means we found one of our cmds  
    free(temp);
    return(flag);
}

/*
int is_valid_file(s_tree *tree, s_minishell *mini)                        
{
    int flag;
    char *path;

    flag = 0;
    if(tree->args && !check_cmd(tree->args[0]) && tree->file_type == READ_FILE)           //if cmd is builtin 
        {
            path = find_cmd_path(tree->args[0], find_path_varibale(mini));                //check for valid path   
            if(!path)
                flag = 0;                                                             //no valid path or cmd does not exist / return 0
            else
            {
                check_permissions(path, tree->args[0], &flag);                        //will check for permission on file and dirs and update flag
            }

        }

}
*/

