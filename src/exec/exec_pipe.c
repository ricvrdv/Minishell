#include "../../inc/minishell.h"

int pipe_and_fork(int *pipefd)
{
    int res;

    res = pipe(pipefd);
    if (res == -1)
        error_exit("Pipe failed!");
    return (0);
}

void child_process(s_tree *node, s_minishell *mini, int *pipefd, int dir)
{
    if (dir == 0)
    {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    }
    execute_node(node, mini, 0, 1);
    exit(0);
}

int execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd)
{
    int pipefd[2];
    int status;
    int final_status;
    pid_t pid;

    pipe_and_fork(pipefd);
    final_status = 0;
    if (tree->left)
    {
        pid = fork();
        if (pid == 0)
            child_process(tree->left, mini, pipefd, 0);
        close(pipefd[1]);
    }
    if (tree->right)
    {
        pid = fork();
        if (pid == 0)
            child_process(tree->right, mini, pipefd, 1);
        close(pipefd[0]);
    }
    while (wait(&status) != -1)
        if (WIFEXITED(status))
            final_status = WEXITSTATUS(status);
    return (exit_code(final_status, 1, 0));
}

/*

int execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    int pipefd[2];
    int status;
    pid_t pid;
    int final_status;

    status = 0;
    final_status = 0;
    if (pipe(pipefd) == -1) 
        error_exit("Pipe failed!");
    if (tree->left) 
    {
        pid = fork();
        if (pid == -1)
            error_exit("Fork failed!");
        if (pid == 0) 
        {
            close(pipefd[0]); // Close the read end of the pipe
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
            close(pipefd[1]); // Close the original write end
            status = execute_node(tree->left, mini, in_fd, out_fd);
            exit(0); // Exit child process
        }
        close(pipefd[1]); // Close the write end in the parent
    }
    if (tree->right) 
    {
        pid = fork();
        if (pid == -1)
            error_exit("Fork failed!");
        if (pid == 0) 
        {
            close(pipefd[1]); // Close the write end of the pipe
            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe
            close(pipefd[0]); // Close the original read end
            status = execute_node(tree->right, mini, in_fd, out_fd);
            exit(0); // Exit child process
        }
        close(pipefd[0]); // Close the read end in the parent
    }
    while (wait(&status) != -1) 
    {
        if (WIFEXITED(status))
            final_status = WEXITSTATUS(status);
    }
    return (exit_code(final_status, 1, 0));
}
*/