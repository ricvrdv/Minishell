#include "../../inc/minishell.h"

static int  update_pwd_vars(s_minishell *mini, char *oldpwd, char *dir);

int    mini_cd(s_minishell *mini, s_tree *node)
{
    char    oldpwd[PATH_MAX];
    int     status;
    char    *dir;

    status = 0;
    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
    {
        perror("minishell: cd");
        return (exit_code(1, 1, 0));
    }
    if (node->argcount > 2)
    {
        ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
        return (exit_code(1, 1, 0));
    }
    if (!mini->cur_dir)
    {
        ft_putstr_fd("cd: current directory not set\n", STDERR_FILENO);
        return (exit_code(1, 1, 0));
    }
    dir = get_target_dir(mini, node->args[1]);
    if (!dir)
        return (1);
    if (chdir(dir) != 0)
    {
        perror("cd");
        free(dir);
        return (1);
    }
    else if (!update_pwd_vars(mini, oldpwd, dir))
        status = 1;
    free(dir);
    sync_env_array(mini);
    return (status);
}

static int  update_pwd_vars(s_minishell *mini, char *oldpwd, char *dir)
{
    char    cwd[PATH_MAX];
    char    *new_pwd;

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        if (dir[0] == '/')
        {
            new_pwd = ft_strdup(dir);
            if (!new_pwd)
                return (0);
        }
        else
        {
            perror("cd: could not get current directory");
            return (0);
        }
    }
    else
    {
        new_pwd = ft_strdup(cwd);
        if (!new_pwd)
            return (0);
    }
    update_env_var(&mini->env, "OLDPWD", oldpwd);
    update_env_var(&mini->env, "PWD", cwd);
    free(mini->cur_dir);
    mini->cur_dir = new_pwd;
    return (1);
}
