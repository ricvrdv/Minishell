#include "../../inc/minishell.h"

int execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    //int fd;

    /*while(mini->heredoc_count >= 0)
    {   
        mini->heredoc_count -=1;
    }*/
    if (tree->type == PIPE) 
        return execute_pipe(tree, mini, in_fd, out_fd);
    else if (tree->type == REDIRECT_L || tree->type == REDIRECT_R 
            || tree->type == APPEND || tree->type == HEREDOC)
        return execute_redirect(tree, mini, in_fd, out_fd);
    else if (tree->type == WORD) 
       return execute_command(tree, mini, in_fd, out_fd);
    return (0);
}


int execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd) 
{
    pid_t pid;
    char *full_path;
    int saved_stdin;
    int saved_stdout;
    int status;

    status = 0;
    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);
    redirect_fds(in_fd, out_fd);
    if (is_builtin(node->args[0]) && in_fd == STDIN_FILENO && out_fd == STDOUT_FILENO)
        status = execute_builtin(node, mini);
    else
    {
        pid = fork();
        if (pid == -1) 
            return report_error(127);
        if (pid == 0) 
        {
            mini->is_child = true;
            if (is_builtin(node->args[0]))
                exit(execute_builtin(node, mini));
            full_path = find_cmd_path(node->args[0], find_path_variable(mini));
            if (full_path == NULL) 
                exit(127);
            if (execve(full_path, node->args, mini->env_array) == -1)
                exit(127);
        }
        else 
        {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                status = 128 + WTERMSIG(status);
        } 
    }
    restore_fd(saved_stdin, saved_stdout);
    return (exit_code(status, 1, 0));
}

int execute_builtin(s_tree *node, s_minishell *mini)
{
    int status;

    status = 0;
    if (ft_strcmp(node->args[0], "cd") == 0)
        status = mini_cd(mini, node);
    else if (ft_strcmp(node->args[0], "echo") == 0)
        status = mini_echo(node);
    else if (ft_strcmp(node->args[0], "pwd") == 0)
        status = mini_pwd(mini);
    else if (ft_strcmp(node->args[0], "export") == 0)
        status = mini_export(mini, node);
    else if (ft_strcmp(node->args[0], "unset") == 0)
        status = mini_unset(mini, node);
    else if (ft_strcmp(node->args[0], "env") == 0)
        status = mini_env(mini, node);
    else if (ft_strcmp(node->args[0], "exit") == 0)
        status = mini_exit(mini, node);
    else 
        status = 127;
    return (exit_code(status, 1, 0));
}

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    return (ft_strcmp(cmd, "cd") == 0 ||
            ft_strcmp(cmd, "echo") == 0 ||
            ft_strcmp(cmd, "pwd") == 0 ||
            ft_strcmp(cmd, "export") == 0 ||
            ft_strcmp(cmd, "unset") == 0 ||
            ft_strcmp(cmd, "env") == 0 ||
            ft_strcmp(cmd, "exit") == 0);
}