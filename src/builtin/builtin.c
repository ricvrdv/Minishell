#include "../../inc/minishell.h"

static s_env   *find_env_var(s_env *env, const char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}



static void    update_env_var(s_env **env, const char *key, const char *value)
{
    s_env   *var;
    s_env   *new_var;
    var = find_env_var(*env, key);
    if (var)
    {
        free(var->value);
        var->value = ft_strdup(value);
        if (!var->value)
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        new_var = malloc(sizeof(s_env));
        if (!new_var)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        new_var->key = ft_strdup(key);
        new_var->value = ft_strdup(value);
        if (!new_var->key || !new_var->value)
        {
            perror("ft_strdup");
            exit(EXIT_FAILURE);
        }
        new_var->next = *env;
        *env = new_var;
    }
}


void    mini_env(char **env_array)
{
    int i;
    i = 0;
    printf("MY ENV:\n");
    while (env_array[i])
    {
        printf("%s\n", env_array[i]);
        i++;
    }
}

void    mini_cd(s_minishell *mini, char **args)
{
    char    *dir;
    char    oldpwd[1024];
    char    cwd[1024];
    s_env   *oldpwd_var;
    s_env   *home_var;
    dir = args[1];
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
            perror("cd: OLDPWD not set\n");
            return ;
        }
        dir = oldpwd_var->value;
    }  
    if (dir == NULL)
    {
        home_var = find_env_var(mini->env, "HOME");
        if (home_var == NULL)
        {
            perror("cd: HOME environment variable not set\n");
            return ;
        }
        dir = home_var->value;
    }
    if (chdir(dir) != 0)
    {
        perror("cd");
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
        exit(EXIT_FAILURE);
    }
}


