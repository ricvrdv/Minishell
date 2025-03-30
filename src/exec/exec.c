#include "../../inc/minishell.h"

void execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd)
{
    int pipefd[2];                                                  //to set pipe
    if (tree->type == PIPE)                                         //we found pipe node
    {
        if (pipe(pipefd) == -1)                                     // Create a pipe
            error_exit("Pipe failed!");
        execute_command(tree->left, mini, in_fd, pipefd[1]);        //execute left side of pipe into write side
        close(pipefd[1]);                                           // Close the write end after forking
        execute_node(tree->right, mini, pipefd[0], out_fd);         // Recursive call for the right side
        close(pipefd[0]);                                           // Close the read end after forking
    }
    else if (tree->type == WORD)
        execute_command(tree, mini, in_fd, out_fd);
}

void execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd)
{
    pid_t pid;                                                      //to know when child or parent process
    char *full_path;                                                //path to cmd

    pid = fork();                                                   //create fork
    if (pid == -1)  
        error_exit("forked failed!");
    if (pid == 0)                                                   // Child process
    {
        if (in_fd != STDIN_FILENO)                                  //used to set up correct fd;
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO)
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        full_path = find_cmd_path(node->args[0], find_path_varibale(mini));     //looks for cdm in in env linked list in mini
        if (full_path == NULL)                                                  //if we dont find dir cmd is not  valid
        {
            fprintf(stderr, "Command not found: %s\n", node->args[0]);
            exit(EXIT_FAILURE);
        }
        if (execve(full_path, node->args, mini->env_array) == -1)               //exec cmd 
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else // Parent process
        waitpid(pid, NULL, 0); // Wait for the child process to finish
}

char *find_path_varibale(s_minishell *mini)
{
    s_env *env;
    env = mini->env;
    while(env)
    {
        if(ft_strncmp(env->key, "PATH", 4) == 0)
            return (env->value + 5);    //skip PATH=
        env = env->next;
    }
    return NULL;
}

char *find_cmd_path(const char *cmd, const char *path)
{
    char **dir;
    char *full_path;
    char *half_path;
    int i;

    i = 0;
    dir = ft_split(path, ':');
    while(dir[i])
    {
        half_path = ft_strjoin(dir[i], "/");
        full_path = ft_strjoin(half_path, cmd);
        free(half_path);
        if(access(full_path, F_OK | X_OK) == 0)
            return full_path;
        free(full_path);
        i++;
    }
    return NULL;
}

void execute_cmd_path(s_minishell *mini, char **cmd, const char *full_path)
{
    if(!cmd || !full_path)
        error_exit("something went wrong");
    if(execve(full_path, cmd, mini->env_array) == -1)
        error_exit("execve failed!");
}