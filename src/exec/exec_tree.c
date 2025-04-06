#include "../../inc/minishell.h"


int exec_tree(s_tree *tree, int *counter, s_minishell *mini)
{
    int     fd[2];
    int     status;

    fd[0] = -1;
    fd[1] = -1;
    if(tree->file_type == TREE_READY)
    {
        if(tree->type == TOKEN)
            status = handle_pipe(tree, counter, mini, fd);                            //tree for node, pipes to keep track ,mini for env, fd to stdin stdout
        if(tree->type == REDIRECT_L || tree->type == REDIRECT_R
            || tree->type == APPEND || tree->type == HEREDOC)                           
            status = handle_redirection(tree, counter, mini, fd);                     //open files , set fds, checks pipes(counters), pid and signals
    }
    if(tree->file_type == CMD_READY)                                                //Node with just a cmd
        status = exec_cmd_node(tree->args, fd, counter, mini);                        //tree->args arg[0]cmd  // will execute the cmd
    status = wait_node(status, counter);                                              //wait for child execution
    if(counter[6])                                                                    //if we have a file to read from 
        close(counter[1]);                                                            ///close current stdin
    if(counter[7])                                                                    //if we have a file to write to
        close(counter[2]);                                                            //close current stdout
    return(status);                                                                 //will pass a message to our update to check what we need to change
}


int exec_cmd_node(char **cmd, int *fd, int *counter, s_minishell *mini)
{
    char    **full_cmd;
    int     status;

    full_cmd = cmd;
    if(check_cmd(cmd[0]))
        status = prep_builtin(full_cmd, fd, mini, counter);                                                                    //prep for cmd builtin
    else
    {
        counter[10] +=1;                                                              //child process count
        if(!counter[8])                                                               //not redirection or pipe
            status = exec_basic_cmd(full_cmd, fd, mini->env, counter);
        else                                                                        //have pipe or redirection
            status = execute_redirection_cmd(full_cmd, fd, mini->env, counter);
    }
    if(counter[0] > 1)                                                                //if i had pipes to execute
        counter[0] -= 1;                                                              //take 1 less since its done
    return (status);
}

int execute_basic_cmd(char **cmd, int *fd, s_minishell *mini, int *counter)
{
    pid_t   pid;
    int     fd_[2];
    char    *path;

    pipe(fd_);
    pid = fork();
    path = find_cmd_path(cmd[0], find_path_varibale(mini));
    if(!pid)
    {
        if(counter[0] && counter[0] <= counter[5])                                      //nbr 0 holds nbr of pipe nodes already executed nbr5 total of pipes
            dup2(fd_[0], 0);
        if(counter[0] > 1)                                                        //
            dup2(fd_[1], 1);
        else
            close(fd_[0]);
        close_pipes(fd_[1], fd_[0]);
        execve(path, cmd[0], mini->env);
    }
    close_pipes(fd_[1], fd[0]);
    if(counter[0] > 1)
        fd = fd_[0];
    else
        close(fd_[0]);
    return 1;
}



void close_pipes(int fd1, int fd2)
{
    close(fd1);
    close(fd2);
}


int handle_pipe(s_tree *tree, int *counter, s_minishell *mini, int *fd)
{
    int status;

    
    if(tree->file_type == CMD_READY)
    {
        counter[8] = 0;
        status = exec_cmd_node(tree->args, fd, counter, mini->env);
    }
    if(tree->type == REDIRECT_L 
            || tree->type == REDIRECT_L
            || tree->type == REDIRECT_R
            || tree->type == APPEND
            || tree->type == HEREDOC)
            return(handle_redirection(tree, counter, mini->env, fd));
    if(tree->left)
        status = handle_pipe(tree->left, counter, mini->env, fd);
    if(tree->right)
        status = handle_pipe(tree->right, counter, mini->env, fd);
    return (status)
}