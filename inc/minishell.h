#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>
#include <signal.h>
# include "Mylib/libft.h"

# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"

typedef struct t_token	s_token;
typedef struct t_env	s_env;
typedef struct t_minishell	s_minishell;
typedef struct t_args       s_args;

typedef enum t_type
{
    PIPE,
    CMD,
    REDIRECT_L,
    REDIRECT_R,
    TRASH,
}   s_type;

typedef struct t_args
{   
    char *value;
    s_args  *next;
}s_args;

typedef struct t_token
{
    char    *type;
    char    *value;
    s_token *next;
}s_token;

typedef struct t_env
{
    char    *key;
    char    *value;
    s_env   *next;
}s_env;

typedef struct t_minishell
{
    int     created;
    char    *cur_dir;
    char    *full_cmd;
    /*int     pid;*/
    s_env   *env;
    s_token *tokens;
    s_args  *args;
}s_minishell;

void	free_struct(s_minishell *mini);
void    init_struct(s_minishell *mini);
void    get_token(s_minishell *mini, char *str);
void    add_token_node(s_token **token_list, char *key, char *code);
void    get_env(s_minishell *mini, char **envp);
void    add_env_node(s_env **env_list, char *key, char *value);
void	clear_token(s_token **token);
void	clear_env(s_env **env);
void    add_args_node(s_args **args_list, char *key);

void    print_tokens(s_minishell *mini);
void    check_cmds(char *str, char **key, char **value);
void    check_signs(char *str, char **key, char **value);



void	mini_exit(s_minishell *mini, char *error);
void	*safe_malloc(size_t bytes);
void	free_stuff(char *str[]);
char    *get_dir();



void    print_env_list(s_env *env_list);
void    print_args(s_minishell *mini);


void    start_prompt(s_minishell **mini);
void	ft_cmd(s_minishell *mini, char *av, int *fd);
char    *find_dir(s_minishell *mini, char *cmd);
void	error_exit(char *error);

char    *s_spaces(char *str);
int     is_space(char *str);
int     check_str(char **line);
int     check_quotes(char *str);
int     invalid_str(char **str);
int     invalid_position(char **str);
int     invalid_operator(char **str);
int     full_check(char *str);
char    *jump_spaces(char *str);
int     check_doubles(char *str);
int     check_redirect(char *str);
int     check_pipe(char *str);
int     space(int c);

#endif
