#include "../../inc/minishell.h"

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

