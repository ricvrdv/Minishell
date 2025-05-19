/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpedro-c <joaopcrema@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:31:00 by Jpedro-c          #+#    #+#             */
/*   Updated: 2025/05/19 17:34:45 by Jpedro-c         ###   ########.fr       */
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
# define BLUE   "\033[1;36m"
# define TREE_READY 100
# define WRITE_FILE 200
# define APPEND_FILE 300
# define READ_FILE 400
# define HEREDOC_FILE 500
# define PIPE_FILE 600
# define CMD_READY 700
# define HEREDOC_EOF_WARNING "warning: here-document delimited by end-of-file\n"

typedef struct s_tree		t_tree;
typedef struct s_token		t_token;
typedef struct s_env		t_env;
typedef struct s_minishell	t_minishell;
typedef enum s_type			t_type;

extern int					g_sig;

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
}	t_type;

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_type			type;
	int				file_type;
	int				argcount;
	char			**args;
	char			*hd_file;
	int				d_quoute;
	int				bad_herdoc;
}	t_tree;

typedef struct s_token
{
	struct s_token	*next;
	t_type			type;
	char			*value;
}	t_token;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

typedef struct s_minishell
{
	struct s_env	*env;
	struct s_tree	*root;
	int				created;
	int				exit_status;
	int				heredoc_count;
	int				heredoc_fd;
	int				heredoc_index;
	bool			is_child;
	char			*cur_dir;
	char			**env_array;
}	t_minishell;

//for init folder
void	add_env_node(t_env **env_list, char *key, char *value);
void	add_token_node(t_token **tokens, t_token *new_token);
void	init_struct(t_minishell *mini);
void	start_prompt(t_minishell **mini);
int		get_env(t_minishell *mini, char **envp);

//for parse folder
int		full_check(char *str);
int		check_quotes(char *str);
int		check_doubles(char *str);
int		check_redirect(char *str);
int		check_pipe(char *str);
int		invalid_operator(char **str);
int		is_space(char *str);
int		check_str(char **line);
char	*s_spaces(char *str);
char	*jump_spaces(char *str);
char	*strip_quotes_and_join(char *input);
char	*join_args(char **args);
void	quote_counter(char c, int *s_counter, int *d_counter);
void	update_quotes(char c, int *inside, char *quote);

//for tokens folder
void	handle_word(char **str, t_token **tokens);
void	handle_sign(char **str, t_token **tokens);
void	put_word(char **start, char **end, t_token **tokens);
t_token	*make_token(char *str, t_token **tokens);
t_token	*get_token(char *str);
t_token	*new_token(t_type type, char *value);

//for builtin folder
int		mini_cd(t_minishell *mini, t_tree *node);
char	*get_target_dir(t_minishell *mini, char *arg);
int		mini_echo(t_tree *node);
int		mini_env(t_minishell *mini, t_tree *node);
int		mini_exit(t_minishell *mini, t_tree *node);
int		is_valid_long(const char *str);
long	calculate_exit_status(const char *arg);
int		mini_export(t_minishell *mini, t_tree *node);
void	print_sorted_env(t_env *env);
void	handle_exit_cleanup(t_minishell *mini, int code);
int		is_valid_identifier(const char *str);
int		mini_pwd(t_minishell *mini);
int		mini_unset(t_minishell *mini, t_tree *node);
void	update_env_var(t_env **env, const char *key, const char *value);
t_env	*find_env_var(t_env *env, const char *key);
void	handle_invalid_identifier(char *arg);
void	sync_env_array(t_minishell *mini);
void	free_array(char **array);
int		is_builtin(char *cmd);
long	ft_atol(const char *nptr);

//for tree folder
int		count_arguments(t_token *current);
int		found_sign(const char *str);
char	*expand_variable(t_minishell *mini, const char *arg);
char	*find_variable(t_minishell *mini, const char *variable);
bool	enclosed_single_quotes(const char *str);
bool	should_expand(const char *str);
void	fill_command_arguments(t_tree *command_node, t_token **tokens,
			int arg_count);
void	prep_tree(t_tree *tree, t_minishell *mini, int *status);
void	count_pipes_redir(t_tree *tree, int *pipes);
void	init_pipes_array(int *pipes, int flag);
void	rename_nodes(t_tree *tree);
void	append_value_to_result(char **res_ptr, const char *value);
void	get_variable_name(const char **ptr, char *var_name);
void	expand_tree(t_minishell *mini, t_tree *tree);
t_tree	*parse_command(t_token **tokens);
t_tree	*parse_token(t_token **tokens);
t_tree	*parse_redirect(t_token **tokens);
t_tree	*parse_pipe(t_token **tokens);
t_tree	*create_arg_node(t_token *token);
t_tree	*create_redirection_node(t_token **tokens, t_token *temp);
t_tree	*new_tree_node(t_type type);
t_tree	*especial_node(t_token **tokens, t_token *temp);

//for exec   
int		check_cmd_access(const char *cmd, t_minishell *mini);
int		execute_builtin(t_tree *node, t_minishell *mini);
int		execute_node(t_tree *tree, t_minishell *mini, int in_fd, int out_fd);
int		execute_pipe(t_tree *tree, t_minishell *mini);
int		execute_redirect(t_tree *tree, t_minishell *mini, int in_fd,
			int out_fd);
int		execute_command(t_tree *node, t_minishell *mini, int in_fd, int out_fd);
int		handle_redirect_r(t_tree *tree);
int		handle_redirect_l(t_tree *tree);
int		handle_append(t_tree *tree);
int		redirect_fds(int in_fd, int out_fd);
int		handle_heredoc(t_tree *node, t_minishell *mini);
int		count_quotes(const char *str);
int		handle_heredocs(t_tree *tree, t_minishell *mini);
int		execute_heredoc(t_tree *tree, t_minishell *mini);
int		execute_last_command(t_tree *node, t_minishell *mini, int in_fd);
int		create_and_fork_command(t_tree *node, t_minishell *mini, int in_fd);
int		handle_parent(pid_t pid);
int		check_quotes_2(const char *str);
char	*find_cmd_path(const char *cmd, const char *path, t_minishell *mini);
char	*find_path_variable(t_minishell *mini);
char	*remove_quotes_redirect(char *str);
void	read_heredoc_expand(int fd, const char *delimiter, t_minishell *mini);
void	restore_fd(int saved_stdin, int saved_stdout);
void	clean_args(char **args, int arg_count);
void	leading_quotes(char *str);
void	remove_trailing(char *arg);
void	read_heredoc(int fd, const char *delimiter);
void	close_heredoc(t_minishell *mini, int fd);
void	print_heredoc(char *str, int fd);
void	remove_quotes(char *arg);
void	handle_expansion_line(int fd, t_minishell *mini, char *line);
void	wait_for_children(int *last_status, pid_t last_pid);
void	invalid_cmd(t_minishell *mini);
void	invalid_path(t_minishell *mini, t_tree *tree);
void	execve_fail(t_minishell *mini);
void	setup_cmd(t_tree *node, int in_fd, int out_fd);
void	write_heredoc(char *str, int fd);
void	handle_heredoc_fork(pid_t pid, t_tree *tree, t_minishell *mini);
bool	is_quoted(const char *delim);
bool	is_dollar_in_single_quotes(const char *str);
pid_t	init_pipe_and_fork(int *pipefd);

//for signals
void	quite_heredoc(int a);
void	ft_sig_restore(void);
void	ft_sig_child(void);
void	ft_sig_mute(void);
void	ft_sigint_handler(int sig);

//for clear
void	clear_env(t_env **env);
void	clear_token(t_token **token);
void	clear_tree(t_tree **tree);
void	clear_env_array(char ***env_array);
void	free_mini_struct(t_minishell *mini);
void	ft_exit(t_minishell *mini, char *error);
void	free_struct(t_minishell *mini);
void	free_split(char **arr);
void	clean_args_expand(char **args);
void	pre_clean_args(char **args, int *argcount);

//for utils folder
int		space(int c);
int		str_size(char *str, char end);
int		exit_code(int exit_status, int write_, int exit_);
int		report_error(int status);
int		static_index(void);
int		extra_mini_exit(t_minishell *mini, t_tree *node);
int		handle_error(char *temp, const char *error_message);
char	*get_dir(void);
char	*generate_file(int index);
char	*strip_quotes(const char *str);
char	*strip_and_join(char *input);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
void	*safe_malloc(size_t bytes);
void	error_exit(char *error);
void	ft_exit_child(t_minishell *mini, char *error);
void	close_fds(void);
bool	has_any_quotes(const char *delim);
bool	are_counts_odd(int d_count, int s_count);
void	ft_sig_child_heredoc(t_minishell *mini);
void	assign_heredoc_filenames(t_tree *tree);
void	print_sigquit(void);
void	print_sigint(void);
void	close_pipefd(int *pipefd);
void	check_builtin(int *status, t_tree *tree, t_minishell *mini);

// valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all --track-fds=yes --show-below-main=no ./minishell 

#endif