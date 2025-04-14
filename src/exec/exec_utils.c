#include "../../inc/minishell.h"


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

    if(cmd[0] == '/')
    {
        if(access(cmd, F_OK | X_OK) == 0)
            return ft_strdup(cmd);
        else
            return NULL;
    }
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