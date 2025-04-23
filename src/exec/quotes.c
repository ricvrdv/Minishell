#include "../../inc/minishell.h"

void remove_quotes(char *arg)
{
    char *read_ptr;
    char *write_ptr;
    int in_single;
    int in_double;

    read_ptr = arg;
	write_ptr = arg;
	in_single = 0;
	in_double = 0;
	while (*read_ptr)
	{
        if (*read_ptr == '\'' && !in_double)
		{
            in_single = !in_single;
            read_ptr++;
        } 
        else if (*read_ptr == '"' && !in_single)
		{
            in_double = !in_double;
            read_ptr++;
        }
        else
			*write_ptr++ = *read_ptr++;
    }
    *write_ptr = '\0';
}

void	clean_args(char **args, int arg_count)
{
	int	index;

	index = 0;
	while (index < arg_count)
	{
		remove_quotes(args[index]);
		index++;
	}
}

void clean_args_redirect(char **args, int arg_count)
{
	int	index;

	index = 0;
	while (index < arg_count)
	{
		remove_quotes_redirect(args[index]);
		index++;
	}
}