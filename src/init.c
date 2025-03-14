#include "../inc/minishell.h"

void    init_struct(s_minishell *mini)
{
    char *curdir;

    mini->created = 1;
    curdir = get_dir(mini);
    mini->cur_dir = curdir;
    mini->full_cmd = NULL;
    mini->env = NULL;
    mini->tokens = NULL;
    
}

char    *get_dir()
{
    char *currentdir = NULL;
    currentdir = getcwd(NULL, 1024);
    return currentdir;
}

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
            add_env_node(&(mini->env), key, value);         //add_node and put key and value
        }   
        i++;
    }
}

void    add_env_node(s_env **env_list, char *key, char *value)
{
    s_env   *new_node;

    new_node = safe_malloc(sizeof(s_env));
    new_node->key = key;
    new_node->value = value;
    new_node->next = *env_list;
    *env_list = new_node;
}

void print_env_list(s_env *env_list)  //for testing
{
    while (env_list)
    {
        printf("%s=%s\n", env_list->key, env_list->value);
        env_list = env_list->next;
    }
}