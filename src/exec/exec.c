#include "../../inc/minishell.h"

void execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    if (tree->type == PIPE) 
        execute_pipe(tree, mini, in_fd, out_fd);
    else if (tree->type == REDIRECT_L || tree->type == REDIRECT_R || tree->type == HEREDOC)
        execute_redirect(tree, mini, in_fd, out_fd);
    else if (tree->type == WORD) 
        execute_command(tree, mini, in_fd, out_fd);
}

void execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    int pipefd[2];

    if (pipe(pipefd) == -1) 
        error_exit("Pipe failed!");
    execute_node(tree->left, mini, in_fd, pipefd[1]);
    close(pipefd[1]); 
    execute_node(tree->right, mini, pipefd[0], out_fd);
    close(pipefd[0]); 
}

void execute_redirect(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    int fd;

    if (tree->type == REDIRECT_L) 
    {
        fd = open(tree->right->args[0], O_RDONLY);
        if (fd == -1) 
        {
            perror("Input redirection failed");
            exit(EXIT_FAILURE);
        }
        execute_node(tree->left, mini, fd, out_fd); // Execute the command with the input redirection
        close(fd);
    } 
    else if (tree->type == REDIRECT_R) 
    {
        fd = open(tree->right->args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) 
        {
            perror("Output redirection failed");
            exit(EXIT_FAILURE);
        }
        execute_node(tree->left, mini, in_fd, fd); // Execute the command with the output redirection
        close(fd);
    }
}

void execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd) 
{
    pid_t pid;
    char *full_path;

    pid = fork();
    if (pid == -1) 
        error_exit("fork failed!");
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
            error_exit("cmd not found!");
        if (execve(full_path, node->args, mini->env_array) == -1)
            error_exit("execve failed!");
    } 
    else  // Parent process
        waitpid(pid, NULL, 0); // Wait for the child process to finish
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

void execute_cmd_path(s_minishell *mini, char **cmd, const char *full_path)
{
    if(!cmd || !full_path)
        error_exit("something went wrong");
    if(execve(full_path, cmd, mini->env_array) == -1)
        error_exit("execve failed!");
}
