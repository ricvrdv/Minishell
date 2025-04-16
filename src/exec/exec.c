#include "../../inc/minishell.h"

int execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    
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
    clean_args(node->args, node->argcount);
    if (is_builtin(node->args[0]))
        execute_builtin(node, mini);
    else
    {
        pid = fork();
        if (pid == -1) 
            return report_error(127);
        if (pid == 0) 
        {
            full_path = find_cmd_path(node->args[0], find_path_variable(mini));
            if (full_path == NULL) 
                exit(127);
            if (execve(full_path, node->args, mini->env_array) == -1)
                exit(127);
        }
        else 
            waitpid(pid, &status, 0); 
    }
    restore_fd(saved_stdin, saved_stdout);
    return status;
}

void execute_builtin(s_tree *node, s_minishell *mini)
{
    if (ft_strcmp(node->args[0], "cd") == 0)
        mini_cd(mini, node);
    else if (ft_strcmp(node->args[0], "echo") == 0)
        mini_echo(node);
    else if (ft_strcmp(node->args[0], "pwd") == 0)
        mini_pwd(mini);
    else if (ft_strcmp(node->args[0], "export") == 0)
        mini_export(mini, node);
    else if (ft_strcmp(node->args[0], "unset") == 0)
        mini_unset(mini, node);
    else if (ft_strcmp(node->args[0], "env") == 0)
        mini_env(mini, node);
    else if (ft_strcmp(node->args[0], "exit") == 0)
        mini_exit(mini, node);
}

int report_error(int status)
{
    return status;
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