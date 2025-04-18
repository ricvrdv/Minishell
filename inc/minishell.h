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
#include "Mylib/libft.h"
#include <limits.h>

# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define MAXARGS 10
# define TREE_READY 100
# define WRITE_FILE 200
# define APPEND_FILE 300
# define READ_FILE 400
# define HEREDOC_FILE 500
# define PIPE_FILE 600
# define CMD_READY 700

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
    APPEND,      //>> append to file
    HEREDOC,    //
    TOKEN,
    FILE_ARG,
    CMD,
}   s_type;

typedef struct s_tree
{
    s_type  type;
    int     file_type;
    int     argcount;
    char    **args;
    int     d_quoute;
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
    int     exit_status;
    bool     is_child;
    int     heredoc_count;
    int     heredoc_fd;
    int     heredoc_index;                           
    char    **env_array;                               
    struct s_env   *env;                                
}s_minishell;


//for init folder
void    add_env_node(s_env **env_list, char *key, char *value);
void    add_token_node(s_token **tokens, s_token *new_token);
void    init_struct(s_minishell *mini);
int     get_env(s_minishell *mini, char **envp);
void    start_prompt(s_minishell **mini);
s_env   *create_env_node(const char *key, const char *value);


//for parse folder
int     full_check(char *str);
int     check_doubles(char *str);
int     check_redirect(char *str);
int     check_pipe(char *str);
int     check_quotes(char *str);
int     invalid_operator(char **str);
int     is_space(char *str);
int     check_str(char **line);
int     empty_quotes(const char *str);
char    *s_spaces(char *str);
char    *jump_spaces(char *str);
void    quote_counter(char c, int *s_counter, int *d_counter);
void    update_quotes(char c, int *inside, char *quote);

//for tokens folder
void    handle_word(char **str, s_token **tokens);
void    handle_sign(char **str, s_token **tokens);
void    put_word(char **start, char **end, s_token **tokens);
s_token *make_token(char *str, s_token **tokens);
s_token *get_token(char *str);
s_token *new_token(s_type type, char *value);

//for builtin folder
int     is_builtin(char *cmd);
int     execute_builtin(s_tree *node, s_minishell *mini);
int     mini_unset(s_minishell *mini, s_tree *node);
int     mini_env(s_minishell *mini, s_tree *node);
int     mini_pwd(s_minishell *mini);
int     mini_cd(s_minishell *mini, s_tree *node);
int     mini_echo(s_tree *node);
int     mini_export(s_minishell *mini, s_tree *node);
int     mini_exit(s_minishell *mini, s_tree *node);
int     ft_strcmp(const char *s1, const char *s2);
int     is_valid_long(const char *str);
int     is_valid_identifier(const char *str);
int     execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd);
s_env   *find_env_var(s_env *env, const char *key);
void    update_env_var(s_env **env, const char *key, const char *value);
void    sync_env_array(s_minishell *mini);
void    free_array(char **array);
void    print_sorted_env(s_env *env);
void    free_struct(s_minishell *mini);
long    ft_atol(const char *nptr);
char    *get_target_dir(s_minishell *mini, char *arg);

//for utils folder
void	error_exit(char *error);
void	*safe_malloc(size_t bytes);
char    *get_dir();
int     space(int c);
bool    are_counts_odd(int d_count, int s_count);
int     str_size(char *str, char end); 

//for signals
void    handle_sigint(int sig);
void    setup_signal_handling(void);

//for tree folder
s_tree	*parse_command(s_token **tokens);
s_tree  *parse_token(s_token **tokens);
s_tree  *parse_redirect(s_token **tokens);
s_tree  *parse_pipe(s_token **tokens);
s_tree	*create_arg_node(s_token *token);
s_tree  *create_redirection_node(s_token **tokens, s_token *temp);
s_tree  *new_tree_node(s_type type);
void	fill_command_arguments(s_tree *command_node, s_token **tokens, int arg_count);
void    prep_tree(s_tree *tree, s_minishell *mini, int *status);
void    count_pipes_redir(s_tree *tree, int *pipes);
void    init_pipes_array(int *pipes, int flag);
void    rename_nodes(s_tree *tree);
int	    count_arguments(s_token *current);
void    print_tree_status(int *pipes, s_tree *tree);
int     check_cmd(char *cmd);
s_tree  *especial_node(s_token **tokens, s_token *temp);


//for clear
void    free_mini_struct(s_minishell *mini);
void	clear_tree(s_tree **tree);
void	clear_env_array(char ***env_array);
void	free_stuff(char *str[]);
void    ft_exit(s_minishell *mini, char *error);
void	clear_token(s_token **token);
void	clear_env(s_env **env);

//for exec   
int     execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd); 
int     execute_pipe(s_tree *tree, s_minishell *mini, int in_fd, int out_fd);
int     execute_redirect(s_tree *tree, s_minishell *mini, int in_fd, int out_fd); 
char    *find_path_variable(s_minishell *mini);
char    *find_cmd_path(const char *cmd, const char *path);
int     report_error(int status);
int     handle_redirect_r(s_tree *tree);
int     handle_redirect_l(s_tree *tree);
int     handle_append(s_tree *tree);
void    restore_fd(int saved_stdin, int saved_stdout);
int     redirect_fds(int in_fd, int out_fd);
void    clean_args(char **args, int arg_count, s_tree *tree);
void    leading_quotes(char *str);
int     count_quotes(const char *str);
void    remove_trailing(char *arg);
int     handle_heredoc(s_tree *node);
void    read_heredoc(int fd, const char *delimiter);

void    expand_tree(s_minishell *mini, s_tree *tree);
char    *expand_variable(s_minishell *mini, const char *arg);
void     get_variable_name(const char **ptr, char *var_name);
void    append_value_to_result(char **res_ptr, const char *value);
char    *ft_strcpy(char *dest, const char *src); 
char    *find_variable(s_minishell *mini, const char *variable);
int     execute_heredoc(s_tree *tree, s_minishell *mini); 
int	    exit_code(int exit_status, int write_, int exit_);
void    remove_quotes(char *arg, s_tree *tree); 



bool	should_expand(const char *str);
bool	enclosed_single_quotes(const char *str);
int     pipe_and_fork(int *pipefd);
void    child_process(s_tree *node, s_minishell *mini, int *pipefd, int dir);

#endif
