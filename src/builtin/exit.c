#include "../../inc/minishell.h"

static int handle_args_offset(s_tree *node);
static bool is_numeric_arg_valid(const char *arg);
static void exit_error(const char *arg, bool numeric_error);
static long calculate_exit_status(const char *arg);

void    mini_exit(s_minishell *mini, s_tree *node)
{
    int arg_offset;
    long    exit_status;

    ft_putstr_fd("exit\n", STDERR_FILENO);
    arg_offset = handle_args_offset(node);
    if (arg_offset == -1)
    {
        free_struct(mini);
        exit (0);
    }
    if (!is_numeric_arg_valid(node->args[arg_offset]))
        exit_error(node->args[arg_offset], true);
    if (node->argcount > arg_offset + 1)
    {
        exit_error(NULL, false);
        return ;
    }
    exit_status = calculate_exit_status(node->args[arg_offset]);
    free_struct(mini);
    exit((int)exit_status);
}

static int handle_args_offset(s_tree *node)
{
    if (node->argcount == 1)
        return (-1);
    
    if (ft_strcmp(node->args[1], "--") == 0)
    {
        if (node->argcount == 2)
            return (-1);
        else
            return (2);
    }
    return (1);
}

static bool is_numeric_arg_valid(const char *arg)
{
    int i;
    
    i = 0;
    if (arg[i] == '+' || arg[i] == '-')
        i++;
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
            return (false);
        i++;
    }
    return (is_valid_long(arg));
}

static void exit_error(const char *arg, bool numeric_error)
{
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    if (numeric_error)
    {
        ft_putstr_fd((char *)arg, STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        exit(2);
    }
    else
        ft_putstr_fd("too many arguments\n", STDERR_FILENO);
}

static long calculate_exit_status(const char *arg)
{
    long status;
    
    status = ft_atol(arg);
    status %= 256;
    if (status < 0)
        status += 256;
    return (status);
}

///////////// BEFORE DIVIDING THE FUNCTION : /////////////////////////

/*
void    mini_exit(s_minishell *mini, s_tree *node)
{
    long    exit_status;
    int     arg_offset;
    int     i;

    arg_offset = 1;
    ft_putstr_fd("exit\n", STDERR_FILENO);
    if (node->argcount == 1)
    {
        free_struct(mini);
        exit(0);
    }
    if(ft_strcmp(node->args[1], "--") == 0)
    {
        if (node->argcount == 2)
        {
            free_struct(mini);
            exit(0);
        }
        arg_offset = 2;
    }
    i = 0;
    if (node->args[arg_offset][i] == '+' || node->args[arg_offset][i] == '-')
        i++;
    while (node->args[arg_offset][i])
    {
        if (!ft_isdigit(node->args[arg_offset][i]))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(node->args[arg_offset], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            free_struct(mini);
            exit(2);
        }
        i++;
    }
    if (node->argcount > arg_offset + 1)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return ;
    }
    if (!is_valid_long(node->args[arg_offset]))
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(node->args[arg_offset], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        free_struct(mini);
        exit(2);
    }
    exit_status = ft_atol(node->args[arg_offset]);
    exit_status = exit_status % 256;
    if (exit_status < 0)
        exit_status += 256;
    free_struct(mini);
    exit((int)exit_status);
}
*/

/*
void    mini_exit(s_minishell *mini, s_tree *node)
{
    int exit_status;
    int is_numeric;
    int i;

    ft_putstr_fd("exit\n", STDERR_FILENO);
    if (node->argcount == 1)
    {
        free_struct(mini);
        exit(0);
    }
    is_numeric = 1;
    i = 0;
    if (node->args[1][i] == '+' || node->args[1][i] == '-')
        i++;
    while (node->args[1][i])
    {
        if (!ft_isdigit(node->args[1][i]))
        {
            is_numeric = 0;
            break ;
        }
        i++;
    }
    if (is_numeric == 0)
    {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(node->args[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        free_struct(mini);
        exit(2);
    }
    if (node->argcount > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return ;
    }
    exit_status = ft_atoi(node->args[1]);
    exit_status = exit_status % 256;
    if (exit_status < 0)
        exit_status = exit_status + 256;
    free_struct(mini);
    exit(exit_status);
}*/