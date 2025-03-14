#include "../inc/minishell.h"


int main()
{
    s_minishell *mini;

    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                       //init values on struc
    printf("Value of teste atm : %i\n", mini->created);
    printf("Current dir: %s\n", mini->cur_dir);

    mini_exit(mini, NULL);
    return 0;
}