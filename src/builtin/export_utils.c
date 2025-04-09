#include "../../inc/minishell.h"

static int  count_env_vars(s_env *env);
static s_env    **env_list_to_array(s_env *env, int count);
static void sort_env_array(s_env **array, int count);
static void print_env_entry(s_env *env);

void    print_sorted_env(s_env *env)
{
    int count;
    int i;
    s_env   **array;

    count = count_env_vars(env);
    array = env_list_to_array(env, count);
    if (!array)
        return ;
    sort_env_array(array, count);
    i = 0;
    while (i < count)
    {
        print_env_entry(array[i]);
        i++;
    }
    free(array);
}

static int  count_env_vars(s_env *env)
{
    int count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

static s_env    **env_list_to_array(s_env *env, int count)
{
    s_env   **array;
    int i;

    array = malloc(count * sizeof(s_env *));
    if (!array)
        return (NULL);
    i = 0;
    while (i < count)
    {
        array[i] = env;
        env = env->next;
        i++;
    }
    return (array);
}

static void sort_env_array(s_env **array, int count)
{
    s_env *temp;
    int i;
    int j;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

static void print_env_entry(s_env *env)
{
    ft_putstr_fd("declare -x ", STDOUT_FILENO);
    ft_putstr_fd(env->key, STDOUT_FILENO);
    if (env->value)
    {
        ft_putstr_fd("=\"", STDOUT_FILENO);
        ft_putstr_fd(env->value, STDOUT_FILENO);
        ft_putstr_fd("\"", STDOUT_FILENO);
    }
    ft_putchar_fd('\n', STDOUT_FILENO);
}

/////////////////////// BEFORE DIVIDING THE FUNCTION : /////////////////
/*
static void print_sorted_env(s_env *env)
{
    int     count;
    s_env   *current;
    s_env   **array;
    s_env   *temp;
    int     i;
    int     j;

    count = 0;
    current = env;
    while (current)
    {
        count++;
        current = current->next;
    }   
    array = malloc(count * sizeof(s_env *));
    if (!array)
        return ;
    current = env;
    i = 0;
    while (current)
    {
        array[i++] = current;
        current = current->next;
    }
    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < count)
    {
        ft_putstr_fd("declare -x ", STDOUT_FILENO);
        ft_putstr_fd(array[i]->key, STDOUT_FILENO);
        if (array[i]->value)
        {
            ft_putstr_fd("=\"", STDOUT_FILENO);
            ft_putstr_fd(array[i]->value, STDOUT_FILENO);
            ft_putstr_fd("\"", STDOUT_FILENO);
        }
        ft_putchar_fd('\n', STDOUT_FILENO);
        i++;
    }
    free(array);
}
*/