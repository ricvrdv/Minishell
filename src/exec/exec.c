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
    if(tree->left)
    status = execute_node(tree->left, mini, in_fd, pipefd[1]);
    close(pipefd[1]);
    if(tree->right)
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
        if(tree->left)
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
        return -1;
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
        return -1;
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
       return -1;
    }
    return fd;
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

void free_struct(s_minishell *mini)
{
    if(mini->cur_dir)
    	free(mini->cur_dir);
    if(mini->env_array)
    	clear_env_array(&mini->env_array);   //todo
    if(mini->env) 
    	clear_env(&mini->env);            //todo
}

void restore_fd(int saved_stdin, int saved_stdout)
{
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
}

int redirect_fds(int in_fd, int out_fd)
{
    if (in_fd != STDIN_FILENO) 
    {
        if(dup2(in_fd, STDIN_FILENO) == -1)
        {   
            perror("dup2 for stdin failed!");
            return -1;
        }
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO) 
    {

        if(dup2(out_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 for stdout failed!");
            return -1;
        }
        close(out_fd);
    }
    return 0;
}
void remove_quotes(char *arg)
{
    int len;

    len = ft_strlen(arg);
    if(len > 1 && arg[0] == '\'' && arg[len - 1] == '\'')     // need to do check for expansions 
    {
        arg[len - 1] = '\0';
        ft_memmove(arg, arg + 1, len - 1); 
    }
    else if(len > 1 && arg[0] == '"' && arg[len - 1] == '"') 
    {
        arg[len - 1] = '\0';
        ft_memmove(arg, arg + 1, len - 1);
    }
}

void clean_args(char **args, int arg_count)
{
    int index;

    index = 0;
    while(index < arg_count)
    {
        remove_quotes(args[index]);
        index++;
    }
}