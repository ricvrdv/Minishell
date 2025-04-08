#include "../../inc/minishell.h"
/*
int exec_tree(s_tree *tree, int *counter, s_minishell *mini)
{
    int     fd[2];
    int     status;

    
    fd[0] = -1;
    fd[1] = -1;
    status = 0;
    if(tree->file_type == TREE_READY)
    {
        if(tree->type == PIPE)
            status = handle_pipe(tree, counter, mini, fd);                            //tree for node, pipes to keep track ,mini for env, fd to stdin stdout
        if(tree->type == REDIRECT_L || tree->type == REDIRECT_R
            || tree->type == APPEND || tree->type == HEREDOC)                           
            status = handle_redirection(tree, counter, mini, fd);                     //open files , set fds, checks pipes(counters), pid and signals
    }
    if(tree->file_type == CMD_READY)                                                //Node with just a cmd
        status = exec_cmd_node(tree, fd, counter, mini);                        //tree->args arg[0]cmd  // will execute the cmd
    status = wait_node(status, counter);                                              //wait for child execution
    if(counter[6])                                                                    //if we have a file to read from 
        close(counter[1]);                                                            ///close current stdin
    if(counter[7])                                                                    //if we have a file to write to
        close(counter[2]);                                                            //close current stdout
    return(status);                                                                 //will pass a message to our update to check what we need to change
}


int exec_cmd_node(s_tree *node, int *fd, int *counter, s_minishell *mini)
{
    int     status;

    if(check_cmd(node->args[0]))
        return 2;                                                                   //prep for cmd builtin
    else
    {
        counter[10] +=1;                                                              //child process count
        if(!counter[8])                                                               //not redirection or pipe
            status = execute_basic_cmd(node, fd, mini, counter);
        else                                                                        //have pipe or redirection
            status = execute_redirection_cmd(node, fd, mini, counter);
    }
    if(counter[0] > 1)                                                                //if i had pipes to execute
        counter[0] -= 1;                                                              //take 1 less since its done
    return (status);
}

int execute_basic_cmd(s_tree *node, int *fd, s_minishell *mini, int *counter)
{
    pid_t   pid;
    int     fd_[2];
    char    *path;
    
    pipe(fd_);                                                                          //create a pipe
    pid = fork();                                                                       //create new process
    path = find_cmd_path(node->args[0], find_path_variable(mini));                      //
    if(!pid)
    {
        if(counter[0] && counter[0] <= counter[5])                                      //if there are pipes to handle
            dup2(fd_[0], 0);                                                            // Redirect stdin to read end of the pipe
        if(counter[0] > 1)                                                              // Redirect stdout to write end of the pipe
            dup2(fd_[1], 1);
        else
            close(fd_[0]);
        close_pipes(fd_[1], fd_[0]);
        execve(path, node->args, mini->env);
    }
    close_pipes(fd_[1], fd[0]);
    if(counter[0] > 1)
        fd = fd_[0];
    else
        close(fd_[0]);
    return 1;                                                                            //sucess
}

int handle_redirection(s_tree *node, int *counter, s_minishell *mini, int *fd)
{
    int status;

    counter[11] = 1;
    if(node->right)
    {
        status = open_redirection(node->right, counter, mini, 0);
        if((status || !node->left) && counter[0] > 1)
            counter[0] -= 1;                                                                //decrement redirection count
    }
    if(node->left && node->left->file_type == CMD_READY && counter[11] && !status)
    {
        counter[8] = 1;                                                                     // Indicate that we are executing a command
        execute_basic_cmd(node->left, fd, mini, counter);                        
    }
    if(node->left && node->left->type == PIPE && counter[11])
        status = handle_pipe(node->left, counter, mini, fd);
    if(node->left && (node->left->type == REDIRECT_L
                || node->left->type == REDIRECT_R
                || node->left->type == HEREDOC
                || node->left->type == APPEND))
        status = handle_redirection(node->left, counter, mini, fd);
    return (status);
}



void close_pipes(int fd1, int fd2)
{
    if(fd1)
        close(fd1);
    if(fd2)
    close(fd2);
}


int handle_pipe(s_tree *tree, int *counter, s_minishell *mini, int *fd)
{
    int status;

    if(tree->file_type == CMD_READY)
    {
        counter[8] = 0;                                                         
        status = exec_cmd_node(tree, fd, counter, mini);
    }
    if(tree->type == REDIRECT_L 
            || tree->type == REDIRECT_L
            || tree->type == REDIRECT_R
            || tree->type == APPEND
            || tree->type == HEREDOC)
            return(handle_redirection(tree, counter, mini, fd));
    if(tree->left)
        status = handle_pipe(tree->left, counter, mini, fd);
    if(tree->right)
        status = handle_pipe(tree->right, counter, mini, fd);
    return (status);
}

int prep_builtin(s_tree *node, int *fd, s_minishell *mini, int *counter)
{
    char *cmd;
    int len;

    (void)mini;
    cmd = node->args[0];
    len = ft_strlen(cmd);
    if (ft_strncmp(cmd, "echo", len) == 0)
        mini_echo(node);
    if (ft_strncmp(cmd, "cd", len) == 0)
        mini_cd(mini, node);
    if (ft_strncmp(cmd, "pwd", len) == 0)
        mini_pwd(mini);
    if (ft_strncmp(cmd, "export", len) == 0)
        mini_export(mini, node);
    if (ft_strncmp(cmd, "env", len) == 0)
        mini_env(mini, node);
    if (ft_strncmp(cmd, "exit", len) == 0)
        mini_exit(mini, node);
    if (ft_strncmp(cmd, "unset", len) == 0)
        mini_unset(mini, node);
}


int open_redirection(s_tree *node, int *counter, s_minishell *mini, int status)
{
    int i;

    if(node->file_type == READ_FILE)
    {
        fd_identifier(counter, 6, 1, 1);
        counter[1] = open(node->args[0], O_RDONLY);                            //set current fd1 ->stdout to  file
        if(counter[1] < 0)
            status = fd_identifier(counter, 0, 0, 0);                              //reset fds;
    }
    else if(node->file_type == WRITE_FILE)
    {
        fd_identifier(counter, 6, 1, 1);
        //status = exec_here_doc(node->args[0], counter, mini->env);
        //handle signs
    }
    else
    {
        fd_identifier(counter, 7, 2, 1);
        i = O_TRUNC;
        if(node->file_type == APPEND_FILE)
            i = O_APPEND;
        counter[2] = open(node->args, O_WRONLY | O_CREAT | i, 0666);
    }
    return (status);
}

int wait_node(int status, int *counter)    //need to check more
{
    if(status != 2 && status != 127
        && status != 126 && counter[10]
        && counter[11])
        {
            while(counter[10])
            {
                wait(&status);
                counter[10] -= 1;
            }
            //signals
        }
    return (status);
}

int execute_redirection_cmd(s_tree *node, int *fd, s_minishell *mini, int *counter)
{
    pid_t pid;
    int fd_[2];
    char    *path;

    pipe(fd_);                                                                          //create a pipe
    pid = fork();                                                                       //create new process
    path = find_cmd_path(node->args[0], find_path_variable(mini)); 
    if(!pid)
    {
        manage_child(counter, fd , fd_);
        execve(path, node->args[0], mini->env);
        exit(1);
    }
    manage_parent(counter, fd, fd_);
    return (1);
}


void manage_child(int *counter, int *fd, int *fd_)
{
	if (counter[8] && counter[6])
	{
		dup2(counter[1], 0);
		close(counter[1]);
	}
	if (counter[8] && counter[7])
	{
		dup2(counter[2], 1);
		close(counter[2]);
	}
	if (counter[0] && counter[0] <= counter[5]
		&& (!counter[8] || !counter[6]))
		dup2(counter[0], 0);
	if (counter[0] > 1 && (!counter[8] || !counter[7]))
		dup2(fd_[1], 1);
	else
		close(fd_[0]);
	close(fd_[0]);
	close(fd_[1]);
}

void manage_parent(int *counter, int *fd, int *fd_)
{
	if (counter[8] && counter[6])
	{
        close(counter[1]);
        counter[6] = 0;
	}
	if (counter[8] && counter[7])
	{
        close(counter[2]);
        counter[7] = 0;
	}
	if (!counter[7] && !counter[6])
		counter[8] = 0;
    close(fd_[1]);
    close(fd[0]);
    if(counter[0] > 1)
        fd[0] = fd_[0];
	else
		close(fd_[0]);
}

*/