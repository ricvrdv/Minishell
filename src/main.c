#include "../inc/minishell.h"

int g_sig = 0;

int main(int ac, char *av[], char **envp)
{
    s_minishell *mini;
    (void)av;

    setup_signal_handling();
    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                       //init values on struc -created-curdir-full_cmd/s_env/s_token
    if(ac == 1 && get_env(mini, envp))
    {
        start_prompt(&mini);
        mini_exit(mini, "Leaving");    
    }
    mini_exit(mini, "No arguments plz");
    return 0;
}

