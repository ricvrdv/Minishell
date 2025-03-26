#include "../inc/minishell.h"

int g_sig = 0;

int main(int ac, char *av[], char **envp)
{
    s_minishell *mini;
    s_env *flex;
    s_env *original;
    (void)ac;
    (void)av;

    mini = safe_malloc(sizeof(s_minishell));  //allocate space for struct
    init_struct(mini);                        //init values on struc -created-curdir-full_cmd/s_env/s_token
    original = create_original_env(envp);
    get_env(&flex, envp);                      //iterates env structs / splits and makes new node(linked list) where it puts info
    setup_signal_handling();
    start_prompt(&mini, original, flex);                       //asks user for input in infinite loop 
    return 0;
}

