#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>


#define MAXARGS 10   //MAX nbr of arguments we can handle

typedef enum s_toke_type
{
    PIPE,
    REDIRECT,
    HERE_DOC,
    EXEC,
}t_token_type;

typedef struct s_cmd
{
    t_token_type type;
}t_cmd;

typedef struct s_token
{


}t_token;