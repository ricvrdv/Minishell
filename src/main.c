#include "../inc/minishell.h"

int g_sig = 0;

int main(int ac, char *av[], char **envp)
{
    s_minishell *mini;
    (void)ac;
    (void)av;

    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                       //init values on struc -created-curdir-full_cmd/s_env/s_token
    get_env(mini, envp);
    setup_signal_handling();
    start_prompt(&mini);
    free_struct(mini);                      //after leaving infinite loop free struct and free mini.
    free(mini);
    return 0;
}

