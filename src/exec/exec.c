#include "../../inc/minishell.h"

int execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    
    if (tree->type == PIPE) 
        return execute_pipe(tree, mini, in_fd, out_fd);
    else if (tree->type == REDIRECT_L || tree->type == REDIRECT_R || tree->type == APPEND)
        return execute_redirect(tree, mini, in_fd, out_fd);
    else if (tree->type == WORD) 
       return execute_command(tree, mini, in_fd, out_fd);
    return (0);
}

int execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    int pipefd[2];
    int status;

    if (pipe(pipefd) == -1) 
        error_exit("Pipe failed!");
    status = execute_node(tree->left, mini, in_fd, pipefd[1]);
    close(pipefd[1]); 
    status = execute_node(tree->right, mini, pipefd[0], out_fd);
    close(pipefd[0]);
    return (status); 
}

int execute_redirect(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    int fd;
    int status;

    status = 0;
    if (tree->type == REDIRECT_L)                                                       // to read from
    {
        fd = handle_redirect_l(tree);
        if (fd == -1) 
            return report_error(127);
        status = execute_node(tree->left, mini, fd, out_fd); // Execute the command with the input redirection
        close(fd);
    } 
    else if (tree->type == REDIRECT_R)                                                          //to write
    {
        fd = handle_redirect_r(tree);
        if (fd == -1) 
            return report_error(127);
        status = execute_node(tree->left, mini, in_fd, fd); // Execute the command with the output redirection
        close(fd);
    }
    else if (tree->type == APPEND)
    {
        fd = handle_append(tree);
        if (fd == -1) 
            return report_error(127);
        status = execute_node(tree->left, mini, in_fd, fd); // Execute the command with the output redirection
        close(fd);
    }
    return status;
}

int handle_redirect_l(s_tree *tree)
{
    int fd;

    fd = open(tree->right->args[0], O_RDONLY);
    if (fd == -1) 
    {
        perror("Input redirection failed");
        return 1;
    }
    return fd;
}

int handle_redirect_r(s_tree *tree)
{
    int fd;

    fd = open(tree->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) 
    {
        perror("Output redirection failed");
        return 1;
    }
    return fd;
}

int handle_append(s_tree *tree)
{
    int fd;

    fd = open(tree->right->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) 
    {
       perror("Output redirection failed");
       return 1;
    }
    return fd;
}

int execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd) 
{
    pid_t pid;
    char *full_path;
    int status;

    status = 0;
    pid = fork();
    if (pid == -1) 
        return report_error(127);
    if (pid == 0) 
    {
        if (in_fd != STDIN_FILENO) 
        {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) 
        {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }
        full_path = find_cmd_path(node->args[0], find_path_variable(mini));
        if (full_path == NULL)
            return report_error(127);
        if (execve(full_path, node->args, mini->env_array) == -1)
            return report_error(127);
    } 
    else  // Parent process
        waitpid(pid, NULL, 0); // Wait for the child process to finish
    return status;

}

char *find_path_variable(s_minishell *mini)
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

int report_error(int status)
{
    return status;
}

