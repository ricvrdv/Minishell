#include "../../inc/minishell.h"

static int handle_args_offset(s_tree *node);
static bool is_numeric_arg_valid(const char *arg);
static void exit_error(const char *arg, bool numeric_error);
static long calculate_exit_status(const char *arg);

int    mini_exit(s_minishell *mini, s_tree *node)
{
    int arg_offset;
    long    exit_status;

    if (!mini->is_child)
        ft_putstr_fd("exit\n", STDOUT_FILENO);
    arg_offset = handle_args_offset(node);
    if (arg_offset == -1)
    {
        free_struct(mini);
        free(mini);
        clear_history();
        clear_tree(&node);
        close(4);
        close(3);
        exit_code(exit_code(0, 0, 0), 0, 1);

    }
    if (!is_numeric_arg_valid(node->args[arg_offset]))
    {
        exit_error(node->args[arg_offset], true);
        free_struct(mini);
        exit_code(2, 1, 1);
    }
    if (node->argcount > arg_offset + 1)
    {
        exit_error(NULL, false);
        return (1);
    }
    exit_status = calculate_exit_status(node->args[arg_offset]);
    free_struct(mini);
    return (exit_code((int)exit_status, 1, 1), (int)exit_status);
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
    bool has_sign;
    
    i = 0;
    has_sign = false;
    if (arg[i] == '+' || arg[i] == '-')
    {
        has_sign = true;
        i++;
    }
    while (arg[i])
    {
        if (!ft_isdigit(arg[i]))
            return (false);
        i++;
    }
    if(has_sign && i == 1)
        return (false);
    if(arg[0] == '+')
        return (is_valid_long(arg + 1));
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
    
    if (*arg == '+')
        arg++;
    status = ft_atol(arg);
    status %= 256;
    if (status < 0)
        status += 256;
    return (status);
}