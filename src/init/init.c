#include "../../inc/minishell.h"

void    init_struct(s_minishell *mini)
{
    char *curdir;

    mini->created = 1;
    curdir = get_dir(mini);
    mini->cur_dir = curdir;
    mini->full_cmd = NULL;
    mini->env = NULL;
    mini->tokens = NULL;
    mini->args = NULL;
    
}

static  char    **create_env_array(char    **envp)
{
    char    **env_array;
    int     count;
    int     i;
    int     j;
    count = 0;
    i = 0;
    while (envp[count])
        count++;
    env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return (NULL);
    while (envp[i])
    {
        env_array[i] = ft_strdup(envp[i]);
        if (!env_array[i])
        {
            j = 0;
            while (j < i)
                free(env_array[j++]);
            free(env_array);
            return (NULL);
        }
        i++;
    }
    env_array[count] = NULL;
    return (env_array);
}

void    get_env(s_minishell *mini, char **envp)
{
    char    *sign;
    char    *key;
    char    *value;
    int     i;
    int     j;
    mini->env_array = create_env_array(envp);
    if (!mini->env_array)
        exit(EXIT_FAILURE);
    i = 0;
    while (envp[i])
    {
        sign = ft_strchr(envp[i], '=');
        if (sign)
        {
            key = ft_substr(envp[i], 0, (sign - envp[i]));
            value = ft_strdup(sign + 1);
            if (!key || !value)
            {
                j = 0;
                while (j <= i)
                    free(mini->env_array[j++]);
                free(mini->env_array);
                exit(EXIT_FAILURE);
            }
            add_env_node(&(mini->env), key, value);
        }
        i++;
    }
}
/*
void   get_env(s_minishell *mini, char **envp)
{
    char        *sign;
    char        *value;
    char        *key;
    int         i;

    i = 0;
    if(!envp || !envp[i] || !mini)
        error_exit("No envp!");
    while(envp[i])
    {
        sign = ft_strchr(envp[i], '=');    // ptr to where = is
        if(sign)
        {
            key = ft_substr(envp[i], 0, (sign - envp[i]));   //everything from start until = included
            value = ft_strdup(sign + 1);                    //everything after =
            add_env_node(&mini->env, key, value);         //add_node and put key and value
        }   
        i++;
    }

}
*/

s_token *new_token(int type)
{
    s_token *token = safe_malloc(sizeof(s_token));
    token->type = type;
    token->value = NULL;
    token->next = NULL;
    return token;
}
