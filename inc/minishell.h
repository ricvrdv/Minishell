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
# define MAXARGS 10

typedef struct s_token	s_token;
typedef struct s_env	s_env;
typedef struct s_minishell	s_minishell;
typedef struct s_args       s_args;


extern int g_sig;

typedef enum s_type
{
    WORD,
    PIPE,
    REDIRECT_L,  //redirect_in
    REDIRECT_R,  //redirect_out
    APPEND,
    HEREDOC,
    TOKEN,
}   s_type;

typedef struct s_args
{   
    char *value;
    s_args  *next;
}s_args;

typedef struct s_tree
{
    s_type  type;
    int     file_type;
    char    **args;
    struct s_tree *left;
    struct s_tree *right;
}s_tree;

typedef struct s_token
{
    s_type    type;
    char      *value;
    struct s_token   *next;
}s_token;

typedef struct s_env
{
    char    *key;
    char    *value;
    struct s_env   *next;
}s_env;

typedef struct s_minishell
{
    int     created;
    char    *cur_dir;
    char    *full_cmd;
    char    **env_array;
    struct s_env   *env;
    struct s_token *tokens;
    struct s_args  *args;
}s_minishell;


//for init
void    add_env_node(s_env **env_list, char *key, char *value);
void    add_token_node(s_token **tokens, s_token *new_token);
void    add_args_node(s_args **args_list, char *key);
void    init_struct(s_minishell *mini);
void    get_env(s_env **env_list, char **envp);
void    start_prompt(s_minishell **mini, s_env *original_env, s_env *flexible_env);
int     check_str(char **line);
s_env   *create_original_env(char **envp);
s_env   *create_env_node(const char *key, const char *value);

//for parse
int     full_check(char *str);
int     check_redirect(char *str);
int     check_doubles(char *str);
int     check_pipe(char *str);
int     check_quotes(char *str);
int     invalid_operator(char **str);
int     is_space(char *str);
int     invalid_position(char **str);
int     empty_quotes(const char *str);
char    *jump_spaces(char *str);
char    *s_spaces(char *str);
void    quote_counter(char c, int *s_counter, int *d_counter);
bool    are_counts_odd(int d_count, int s_count);
int	    count_arguments(s_token *current);
void	fill_command_arguments(s_tree *command_node, s_token **tokens, int arg_count);

//for tokens
void    handle_sign(char **str, s_token **tokens);
void    handle_word(char **str, s_token **tokens);
void    update_quotes(char c, int *inside, char *quote);
void    put_word(char **start, char **end, s_token **tokens);
s_token *make_token(char **str, s_token **tokens);
s_token *get_token(char *str);
s_token *new_token(s_type type, char *value);

//for builtin
void    mini_env(char **env_array);
void    mini_cd(s_minishell *mini, char **args);
void    execute_command(s_minishell *mini, char **cmd);

//for utils
void	clear_env(s_env **env);
void	clear_token(s_token **token);
void	mini_exit(s_minishell *mini, char *error);
void	error_exit(char *error);
void	*safe_malloc(size_t bytes);
void	free_struct(s_minishell *mini);
void	free_stuff(char *str[]);
char    *get_dir();
int     space(int c);

//for sigaction
void    handle_sigint(int sig);
void    setup_signal_handling(void);

//for tree
s_tree	*parse_command(s_token **tokens);
s_tree  *parse_token(s_token **tokens);
s_tree  *parse_redirect(s_token **tokens);
s_tree  *parse_pipe(s_token **tokens);
s_tree	*create_arg_node(s_token *token);
s_tree  *create_redirection_node(s_token **tokens, s_token *temp);
s_tree  *new_tree_node(s_type type);


//for testing
void print_token_list(s_token *token_list);
void print_token(s_token *tokens);
const char *token_name(s_type type);
void ft_print_tree(s_tree *tree);
void print_env_list(s_env *env);

#endif
