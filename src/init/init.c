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


s_token *new_token(s_type type, char *value)
{
    s_token *token;

    token = safe_malloc(sizeof(s_token));
    if(!token)
        return (NULL);
    token->type = type;
    token->value = ft_strdup(value);
    if(!token->value)
    {
        free(token);
        return (NULL);
    }
    token->next = NULL;
    return (token);
}

s_tree *new_tree_node(s_type type)
{
    s_tree *node;
    
    node = safe_malloc(sizeof(s_tree));
    node->type = type;
    node->args = NULL;
    node->left = NULL;
    node->right = NULL;
    return (node);
}