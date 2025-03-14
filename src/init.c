#include "../inc/minishell.h"

void    init_struct(s_minishell *mini)
{
    char *curdir;

    mini->created = 1;
    curdir = get_dir(mini);
    mini->cur_dir = curdir;
    mini->full_cmd = NULL;
    
}

char    *get_dir()
{
    char *currentdir = NULL;
    currentdir = getcwd(NULL, 1024);
    return currentdir;
}
