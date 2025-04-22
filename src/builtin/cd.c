#include "../../inc/minishell.h"

static int  update_pwd_vars(s_minishell *mini, char *oldpwd);

int    mini_cd(s_minishell *mini, s_tree *node)
{
    char    oldpwd[PATH_MAX];
    char    *dir;

    if(node->argcount > 2)
    {
        ft_putstr_fd(" too many arguments\n", 2);
        return(1);
    }
    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
    {
        perror("cd: could not get current directory");
        return (1);
    }
    dir = get_target_dir(mini, node->args[1]);
    if (!dir)
        return (1);
    if (chdir(dir) != 0)
    {
        perror("cd");
        return (free(dir), 1);
    }
    if (!update_pwd_vars(mini, oldpwd))
        return (free(dir), 1);
    free(dir);
    sync_env_array(mini);
    return (0);
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
