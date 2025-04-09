#include "../../inc/minishell.h"

s_env   *find_env_var(s_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}

void    update_env_var(s_env **env, const char *key, const char *value)
{
    s_env   *var;
    s_env   *new_var;
    
    var = find_env_var(*env, key);
    if (var)
    {
        free(var->value);
        if (value)
            var->value = ft_strdup(value);
        else
            var->value = NULL;
        if (value && !var->value)
            exit(EXIT_FAILURE);
    }
    else
    {
        new_var = malloc(sizeof(s_env));
        if (!new_var)
            exit(EXIT_FAILURE);
        new_var->key = ft_strdup(key);
        if (value)
            new_var->value = ft_strdup(value);
        else
            new_var->value = NULL;
        if (!new_var->key || (value && !new_var->value))
        {
            free(new_var->key);
            free(new_var);
            exit(EXIT_FAILURE);
        }
        new_var->next = *env;
        *env = new_var;
    }
}

void    sync_env_array(s_minishell *mini)
{
    int     count;
    s_env   *current;
    char    **new_array;
    int     i;
    char    *tmp;

    if (!mini)
        return ;
    free_array(mini->env_array);
    mini->env_array = NULL;
    count = 0;
    current = mini->env;
    i = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    new_array = malloc((count + 1) * sizeof(char *));
    if (!new_array)
        return ;
    current = mini->env;
    while (current)
    {
        if (current->value)
        {
            tmp = ft_strjoin(current->key, "=");
            if (!tmp)
            {
                free_array(new_array);
                return ;
            }
            new_array[i] = ft_strjoin(tmp, current->value);
            free(tmp);
        }
        else
            new_array[i] = ft_strdup(current->key);
        if (!new_array[i])
        {
            free_array(new_array);
            return ;
        }
        i++;
        current = current->next;
    }
    new_array[i] = NULL;
    mini->env_array = new_array;
}

void    free_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
        free(array[i++]);
    free(array);
}

int is_valid_identifier(const char *str)
{
    if (!str || !*str)
        return (0);
    if (!ft_isalpha(*str) && *str != '_')
        return (0);
    while (*++str)
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
    return (1);
}