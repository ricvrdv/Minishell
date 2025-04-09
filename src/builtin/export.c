#include "../../inc/minishell.h"

static void export_argument(s_minishell *mini, char *arg);
static void append_to_env_var(s_minishell *mini, char *arg, char *plus_sign);
static void assign_env_var(s_minishell *mini, char *arg, char *equal_sign);
static void handle_invalid_identifier(char *arg);

void    mini_export(s_minishell *mini, s_tree *node)
{
    int i;

    if (node->argcount == 1)
    {
        print_sorted_env(mini->env);
        return ;
    }
    i = 1;
    while (i < node->argcount)
    {
        export_argument(mini, node->args[i]);
        i++;
    }
    sync_env_array(mini);
}

static void export_argument(s_minishell *mini, char *arg)
{
    char    *equal_sign;
    char    *plus_sign;

    equal_sign = ft_strchr(arg, '=');
    if (equal_sign)
    {
        plus_sign = ft_strchr(arg, '+');
        if (plus_sign && plus_sign + 1 == equal_sign)
            append_to_env_var(mini, arg, plus_sign);
        else
            assign_env_var(mini, arg, equal_sign);
    }
    else
    {
        if (!is_valid_identifier(arg))
        {
            handle_invalid_identifier(arg);
            return ;
        }
        if (!find_env_var(mini->env, arg))
            add_env_node(&mini->env, ft_strdup(arg), NULL);
    }
}

static void append_to_env_var(s_minishell *mini, char *arg, char *plus_sign)
{
    char    *key;
    char    *value;
    char    *new_value;
    s_env   *var;

    key = ft_substr(arg, 0, plus_sign - arg);
    value = ft_strdup(plus_sign + 2);
    if (!is_valid_identifier(key))
    {
        handle_invalid_identifier(key);
        return (free(key), free(value));
    }
    var = find_env_var(mini->env, key);
    if (var)
    {
        new_value = ft_strjoin(var->value, value);
        free(var->value);
        var->value = new_value;
    }
    else
        update_env_var(&mini->env, key, value);
    free(key);
    free(value);
}

static void assign_env_var(s_minishell *mini, char *arg, char *equal_sign)
{
    char    *key;
    char    *value;

    key = ft_substr(arg, 0, equal_sign - arg);
    if (*key == '\0')
    {
        free(key);
        key = ft_strdup(arg);
    }
    value = ft_strdup(equal_sign + 1);
    if (!is_valid_identifier(key))
    {
        handle_invalid_identifier(arg);
        return (free(key), free(value));
    }
    update_env_var(&mini->env, key, value);
    free(key);
    free(value);
}

static void handle_invalid_identifier(char *arg)
{
    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

///////////// BEFORE DIVIDING THE FUNCTION : /////////////////////////
/*
void    mini_export(s_minishell *mini, s_tree *node)
{
    int     i;
    char    *sign;
    char    *key;
    char    *value;
    char    *append;
    char    *new_value;
    s_env   *var;

    if (node->argcount == 1)
    {
        print_sorted_env(mini->env);
        return ;
    }
    i = 1;
    while (i < node->argcount)
    {
        sign = ft_strchr(node->args[i], '=');
        if (sign)
        {
            append = ft_strchr(node->args[i], '+');
            if (append && *(append + 1) == '=')
            {
                key = ft_substr(node->args[i], 0, append - node->args[i]);
                value = ft_strdup(append + 2);
                if (!is_valid_identifier(key))
                {
                    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
                    ft_putstr_fd(key, STDERR_FILENO);
                    ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
                    free(key);
                    free(value);
                    i++;
                    continue ;
                }
                var = find_env_var(mini->env, key);
                if (var)
                {
                    new_value = ft_strjoin(var->value, value);
                    free(var->value);
                    var->value = new_value;
                }
                else
                    update_env_var(&mini->env, key, value);
                free(key);
                free(value);
            }
            else
            {
                key = ft_substr(node->args[i], 0, sign - node->args[i]);
				if (*key == '\0')
				{
					free(key);
					key = ft_strdup(node->args[i]);
				}
                value = ft_strdup(sign + 1);
                if (!is_valid_identifier(key))
                {
                    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
                    ft_putstr_fd(node->args[i], STDERR_FILENO);
                    ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
                    free(key);
                    free(value);
                    i++;
                    continue ;
                }
                update_env_var(&mini->env, key, value);
                free(key);
                free(value);
            }
        }
        else
        {
            key = ft_strdup(node->args[i]);
            if (!is_valid_identifier(key))
            {
                ft_putstr_fd("minishell: export: `", STDERR_FILENO);
                ft_putstr_fd(key, STDERR_FILENO);
                ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
                free(key);
                i++;
                continue ;
            }
            if (!find_env_var(mini->env, key))
                add_env_node(&mini->env, key, NULL);
            free(key);
        }
        i++;
    }
    sync_env_array(mini);
}*/
