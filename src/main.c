#include "minishell.h"

int main()
{
    char *line;
    char buffer[256];
    char *currentdir;
    
    currentdir = getcwd(NULL, 1024);
    while((line = readline("> ")) != NULL)
    {
        strncpy(buffer, line, 256);
        get_token(buffer);
        printf("%s\n", buffer);
        add_history(line);

    }
    free(line);
    clear_history();
    return 0;
}