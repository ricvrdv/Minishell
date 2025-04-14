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
/*
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
*/

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
        if(tree->left)
            status = execute_node(tree->left, mini, in_fd, fd); // Execute the command with the output redirection
        close(fd);
    }
    else if (tree->type == HEREDOC)
    {
        fd = handle_heredoc(tree);
        if (fd == -1) 
            return report_error(127);
        status = execute_node(tree->left, mini, fd, out_fd); // Execute the command with the output redirection
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

int execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd) 
{
    int pipefd[2];
    int status;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    if (pipe(pipefd) == -1) 
        error_exit("Pipe failed!");
    if (tree->left) 
    {
        pid_t pid = fork();
        if (pid == -1)
            error_exit("Fork failed!");
        if (pid == 0) {
            // Child process
            close(pipefd[0]); // Close the read end of the pipe
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
            close(pipefd[1]); // Close the original write end
            execute_node(tree->left, mini, in_fd, out_fd);
            exit(0); // Exit child process
        }
        close(pipefd[1]); // Close the write end in the parent
    }
    if (tree->right) 
    {
        pid_t pid = fork();
        if (pid == -1)
            error_exit("Fork failed!");
        if (pid == 0) {
        
            close(pipefd[1]); // Close the write end of the pipe
            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe
            close(pipefd[0]); // Close the original read end
            execute_node(tree->right, mini, in_fd, out_fd);
            exit(0); // Exit child process
        }
        close(pipefd[0]); // Close the read end in the parent
    }
  
    wait(NULL);
    wait(NULL);
    return 0; // Return success
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

int handle_heredoc(s_tree *node)
{
    const char *delimeter;
    char *temp_file;
    int fd;
    
    delimeter = node->right->args[0];
    temp_file = "/tmp/heredoc_temp.txt";                                           //temp file
    fd = open (temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);                      //redirect to temp file
    if(fd == -1)
        return -1;
    read_heredoc(fd, delimeter);
    close(fd);
    return open(temp_file, O_RDONLY);

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

void read_heredoc(int fd, const char *delimiter)
{
    char *line;
    size_t len;

    len = ft_strlen(delimiter);
    while(1)
    {
        line = readline("> ");
        if(!line)
            break;
        if(ft_strncmp(line, delimiter, len) == 0)
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
    }
}
