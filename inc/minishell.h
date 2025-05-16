/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:31:00 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/16 13:40:54 by Jpedro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdbool.h>
# include <signal.h>
# include "Mylib/libft.h"
# include <limits.h>

# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define TREE_READY 100
# define WRITE_FILE 200
# define APPEND_FILE 300
# define READ_FILE 400
# define HEREDOC_FILE 500
# define PIPE_FILE 600
# define CMD_READY 700
# define HEREDOC_EOF_WARNING "warning: here-document delimited by end-of-file\n"

typedef struct s_token      s_token;
typedef struct s_env        s_env;
typedef struct s_minishell  s_minishell;
typedef struct s_args       s_args;


extern int g_sig;

typedef enum s_type
{
    WORD,       
    PIPE,
    REDIRECT_L,
    REDIRECT_R,  
    APPEND,      
    HEREDOC,   
    TOKEN,
    FILE_ARG,
    CMD,
}   s_type;

typedef enum e_signal
{
	PARENT_,
	CHILD_,
	HERE_SIG,
	DEFAULT_,
}	t_signal;

typedef struct s_tree
{
    s_type  type;
    int     file_type;
    int     argcount;
    char    **args;
    char    *hd_file;
    int     d_quoute;
    int     bad_herdoc;  
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
    int     exit_status;
    int     heredoc_count;
    int     heredoc_fd;
    int     heredoc_index;                        
    bool     is_child;
    char    *cur_dir;
    char    **env_array;                               
    struct s_env   *env;  
    struct s_tree  *root;                              
}s_minishell;


//for init folder
void    add_env_node(s_env **env_list, char *key, char *value);
void    add_token_node(s_token **tokens, s_token *new_token);
void    init_struct(s_minishell *mini);
void    start_prompt(s_minishell **mini);
int     get_env(s_minishell *mini, char **envp);

//for parse folder
int     full_check(char *str);
int     check_quotes(char *str);
int     check_doubles(char *str);
int     check_redirect(char *str);
int     check_pipe(char *str);
int     invalid_operator(char **str);
int     is_space(char *str);
int     check_str(char **line);
char    *s_spaces(char *str);
char    *jump_spaces(char *str);
char	*strip_quotes_and_join(char *input);
char	*join_args(char **args);
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
int     mini_cd(s_minishell *mini, s_tree *node);
char    *get_target_dir(s_minishell *mini, char *arg);
int     mini_echo(s_tree *node);
int     mini_env(s_minishell *mini, s_tree *node);
int     mini_exit(s_minishell *mini, s_tree *node);
int     is_valid_long(const char *str);
long    calculate_exit_status(const char *arg);
int     mini_export(s_minishell *mini, s_tree *node);
void    print_sorted_env(s_env *env);
void	handle_exit_cleanup(s_minishell *mini, int code);
int     is_valid_identifier(const char *str);
int     mini_pwd(s_minishell *mini);
int     mini_unset(s_minishell *mini, s_tree *node);
void    update_env_var(s_env **env, const char *key, const char *value);
s_env   *find_env_var(s_env *env, const char *key);
void    handle_invalid_identifier(char *arg);
void    sync_env_array(s_minishell *mini);
void    free_array(char **array);
int     is_builtin(char *cmd);
long    ft_atol(const char *nptr);

//for tree folder
int	    count_arguments(s_token *current);
int	    found_sign(const char *str);
char    *expand_variable(s_minishell *mini, const char *arg);
char    *find_variable(s_minishell *mini, const char *variable);
bool	enclosed_single_quotes(const char *str);
bool	should_expand(const char *str);
void	fill_command_arguments(s_tree *command_node, s_token **tokens, int arg_count);
void    prep_tree(s_tree *tree, s_minishell *mini, int *status);
void    count_pipes_redir(s_tree *tree, int *pipes);
void    init_pipes_array(int *pipes, int flag);
void    rename_nodes(s_tree *tree);
void    append_value_to_result(char **res_ptr, const char *value);
void    get_variable_name(const char **ptr, char *var_name);
void    expand_tree(s_minishell *mini, s_tree *tree);
s_tree	*parse_command(s_token **tokens);
s_tree  *parse_token(s_token **tokens);
s_tree  *parse_redirect(s_token **tokens);
s_tree  *parse_pipe(s_token **tokens);
s_tree	*create_arg_node(s_token *token);
s_tree  *create_redirection_node(s_token **tokens, s_token *temp);
s_tree  *new_tree_node(s_type type);
s_tree  *especial_node(s_token **tokens, s_token *temp);

//for exec   
int	    check_cmd_access(const char *cmd, s_minishell *mini);
int     execute_builtin(s_tree *node, s_minishell *mini);
int     execute_node(s_tree *tree, s_minishell *mini, int in_fd, int out_fd); 
int     execute_pipe(s_tree *tree, s_minishell *mini);
int     execute_redirect(s_tree *tree, s_minishell *mini, int in_fd, int out_fd); 
int     execute_command(s_tree *node, s_minishell *mini, int in_fd, int out_fd);
int     handle_redirect_r(s_tree *tree);
int     handle_redirect_l(s_tree *tree);
int     handle_append(s_tree *tree);
int     redirect_fds(int in_fd, int out_fd);
int	    handle_heredoc(s_tree *node, s_minishell *mini);
int     count_quotes(const char *str);
int     handle_heredocs(s_tree *tree, s_minishell *mini);
int     execute_heredoc(s_tree *tree, s_minishell *mini);
int     execute_last_command(s_tree *node, s_minishell *mini, int in_fd);
int     create_and_fork_command(s_tree *node, s_minishell *mini, int in_fd);
int	    handle_parent(pid_t pid);
int	    handle_heredoc_wait(int pid,s_tree *node);
int	    check_quotes_2(const char *str);
char    *find_cmd_path(const char *cmd, const char *path, s_minishell *mini);
char    *find_path_variable(s_minishell *mini);
char	*remove_quotes_redirect(char *str);
void    read_heredoc_expand(int fd, const char *delimiter, s_minishell *mini);
void    restore_fd(int saved_stdin, int saved_stdout);
void    clean_args(char **args, int arg_count);
void    leading_quotes(char *str);
void    remove_trailing(char *arg);
void    read_heredoc(int fd, const char *delimiter);
void    close_heredoc(s_minishell *mini, int fd);
void    print_heredoc(char *str, int fd);
void    remove_quotes(char *arg);
void    handle_expansion_line(int fd, s_minishell *mini, char *line);
void    wait_for_children(int *last_status, pid_t last_pid);
void	invalid_cmd(s_minishell *mini);
void    invalid_path(s_minishell *mini);
void    execve_fail(s_minishell *mini);
void    setup_cmd(s_tree *node, int in_fd, int out_fd);
void    write_heredoc(char *str, int fd);
bool	is_quoted(const char *delim);
bool	is_dollar_in_single_quotes(const char *str);
pid_t	init_pipe_and_fork(int *pipefd);

//for signals
void	handle_ctrl_c(int a);
void	setup_signal_handlers(void);
void	child_ctrl_c(int sig_num);
void	quite_heredoc(int a);
void	ft_sig_restore(void);
void	ft_sig_child(void);
void	ft_sig_mute(void);
void	ft_sig_child_handler(int signo, s_minishell *mini);
void    ft_sigint_handler(int sig); 

//for clear
void	clear_env(s_env **env);
void	clear_token(s_token **token);
void	clear_tree(s_tree **tree);
void	clear_env_array(char ***env_array);
void    free_mini_struct(s_minishell *mini);
void    ft_exit(s_minishell *mini, char *error);
void    free_struct(s_minishell *mini);
void	free_split(char **arr);
void	clean_args_expand(char **args);
void	pre_clean_args(char **args, int *argcount);

//for utils folder
int     space(int c);
int     str_size(char *str, char end); 
int	    exit_code(int exit_status, int write_, int exit_);
int     report_error(int status);
int     is_directory(const char *path);
int	    static_index(void);
int	    extra_mini_exit(s_minishell *mini, s_tree *node);
int     handle_error(char *temp, const char *error_message);
char    *get_dir(void);
char	*generate_file(int index);
char    *strip_quotes(const char *str);
char	*strip_and_join(char *input);
char	*ft_strcat(char *dest, const char *src);
char    *ft_strcpy(char *dest, const char *src); 
void	*safe_malloc(size_t bytes);
void	error_exit(char *error);
void	ft_exit_child(s_minishell *mini, char *error);
void	close_fds(void);
bool	has_any_quotes(const char *delim);
bool    are_counts_odd(int d_count, int s_count);
void 	ft_sig_child_heredoc(s_minishell *mini);
void handle_all_heredocs_in_child(s_tree *tree, s_minishell *mini);


//  valgrind --leak-check=full --show-leak-kinds=definite ./minishell
// valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all --track-fds=yes --show-below-main=no ./minishell 

#endif