#include "../../inc/minishell.h"

void handle_sigint(int sig) 
{
    (void)sig;
    printf("\n");  // Print a new line to avoid "^C"
    rl_on_new_line();      // Reset Readline's internal state
    rl_replace_line("", 0); // Clear input buffer
    rl_redisplay();  
}

void setup_signal_handling(void) 
{
    struct sigaction action; // Declare the sigaction struct
    memset(&action, 0, sizeof(action)); // Initialize the struct to zero
    action.sa_handler = handle_sigint;   // Set the handler function
    sigaction(SIGINT, &action, NULL);     // Register the signal handler
}