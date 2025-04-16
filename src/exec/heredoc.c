#include "../../inc/minishell.h"

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