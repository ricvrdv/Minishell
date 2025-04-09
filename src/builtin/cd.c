#include "../../inc/minishell.h"

static int  update_pwd_vars(s_minishell *mini, char *oldpwd);

void    mini_cd(s_minishell *mini, s_tree *node)
{
    char    oldpwd[PATH_MAX];
    char    *dir;

    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
    {
        perror("cd: could not get current directory");
        return ;
    }
    dir = get_target_dir(mini, node->args[1]);
    if (!dir)
        return ;
    if (chdir(dir) != 0)
    {
        perror("cd");
        free(dir);
        return ;
    }
    if (!update_pwd_vars(mini, oldpwd))
    {
        free(dir);
        return ;
    }
    free(dir);
    sync_env_array(mini);
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

///////////// BEFORE DIVIDING THE FUNCTION : /////////////////////////
/*
void    mini_cd(s_minishell *mini, s_tree *node)
{
    char    *dir;
    char    oldpwd[1024];
    char    cwd[1024];
    s_env   *oldpwd_var;
    s_env   *home_var;
    char    *expanded_dir;
    
    dir = node->args[1];
    expanded_dir = NULL;
    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
    {
        perror("cd: could not get current directory");
        return ;
    }
    if (dir != NULL && ft_strncmp(dir, "-", ft_strlen(dir)) == 0)
    {
        oldpwd_var = find_env_var(mini->env, "OLDPWD");
        if (oldpwd_var == NULL)
        {
            perror("cd: OLDPWD not set");
            return ;
        }
        dir = oldpwd_var->value;
        printf("%s\n", oldpwd_var->value);
    }  
    if (dir == NULL || ft_strncmp(dir, "~", ft_strlen(dir)) == 0)
    {
        home_var = find_env_var(mini->env, "HOME");
        if (home_var == NULL)
        {
            perror("cd: HOME not set");
            return ;
        }
        dir = home_var->value;
    }
    if (dir[0] == '~' && dir[1] == '/')
    {
        home_var = find_env_var(mini->env, "HOME");
        if (!home_var)
        {
            perror("cd: HOME not set");
            return ;
        }
        expanded_dir = ft_strjoin(home_var->value, dir + 1);
        if (!dir)
        {
            perror("Error: Failed ft_strjoin");
            return ;
        }
        dir = expanded_dir;
    }
    if (chdir(dir) != 0)
    {
        perror("cd");
        if (expanded_dir)
            free(expanded_dir);
        return ;
    }
    update_env_var(&mini->env, "OLDPWD", oldpwd);
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("cd: could not get current directory");
        return ;
    }
    update_env_var(&mini->env, "PWD", cwd);
    free(mini->cur_dir);
    mini->cur_dir = ft_strdup(cwd);
    if (!mini->cur_dir)
    {
        perror("ft_strdup");
        if(expanded_dir)
            free(expanded_dir);
        exit(EXIT_FAILURE);
    }
    if (expanded_dir)
        free(expanded_dir);
    sync_env_array(mini);
}
*/