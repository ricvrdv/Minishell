#include "../../inc/minishell.h"

static int  update_pwd_vars(s_minishell *mini, char *oldpwd);

int    mini_cd(s_minishell *mini, s_tree *node)
{
    char    oldpwd[PATH_MAX];
    char    *dir;
    int     status;

    status = 0;
    if(node->argcount > 2)
    {
        ft_putstr_fd(" too many arguments\n", 2);
        return (exit_code(1, 1, 0));
    }
    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
    {
        perror("cd: could not get current directory");
        return (exit_code(1, 1, 0));
    }
    dir = get_target_dir(mini, node->args[1]);
    if (!dir || chdir(dir) != 0)
    {
        perror("cd");
        status = 1;
    }
    else if (!update_pwd_vars(mini, oldpwd))
        status = 1;
    free(dir);
    sync_env_array(mini);
    return (exit_code(status, 1, 0));
}

static int  update_pwd_vars(s_minishell *mini, char *oldpwd)
{
    char    cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("cd: could not get current directory");
        return (0);
    }
    update_env_var(&mini->env, "OLDPWD", oldpwd);
    update_env_var(&mini->env, "PWD", cwd);
    free(mini->cur_dir);
    mini->cur_dir = ft_strdup(cwd);
    if (!mini->cur_dir)
    {
        perror("ft_strdup");
        exit(EXIT_FAILURE);
    }
    return (1);
}
