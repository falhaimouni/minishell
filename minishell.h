/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falhaimo <falhaimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:31:43 by sshawish          #+#    #+#             */
/*   Updated: 2025/04/08 23:26:33 by falhaimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/stat.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

# define MAX_ARGS 100
# define MAX_BUF 1024

extern volatile sig_atomic_t	g_sig;

typedef struct s_redirection
{
	struct s_redirection	*next;
	char					*filename;
	int						type;
	int						pipe_fd[2];
	char					*heredoc_content;
}	t_redirection;

typedef struct s_shell
{
	char	**tokens;
	char	*user_input;
}	t_shell;

typedef struct s_command
{
	t_redirection	*redirections;
	char			*cmd;
	char			**args;
	char			*input;
	char			*output;
	char			*pipe;
	char			*heredoc;
	int				append;
	t_shell			*shell;
}	t_command;

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
	int				exit_status;
	int				qouted;
	char			*pwd;
	int				redir_flag;
	int				lex_flag;
}	t_env;	

typedef struct s_lex
{
	char	**tokens;
	char	*current_token;
	char	*ptr;
	char	quote_char;
	bool	in_quotes;
	int		i;
	int		in_heredoc;
}	t_lex;

typedef struct s_pipe_data
{
	int			i;
	int			old_fd;
	int			*fd;
	pid_t		pid;
	t_command	**commands;
	t_shell		data;
	t_env		*env;
	int			num_commands;
}	t_pipe_data;

typedef struct s_pipe_vars
{
	int			i;
	int			old_fd;
	int			fd[2];
	pid_t		pid;
}	t_pipe_vars;

typedef struct s_buffer
{
	char	*content;
	size_t	size;
	size_t	capacity;
}	t_buffer;

t_command	*parse(char **tokens, int *i);
t_command	**parse_all_commands(char **tokens, int *num_commands);
t_env		*copy_env(char **envp);
t_env		*new_env_node(char *env);
t_env		*copy_env_sort(t_env *env);
t_env		*create_env_node(t_env *temp);
t_env		*lstlast(t_env *lst);
t_env		*free_env_list_on_error(t_env *head);
int			get_envp_length(t_env *env);
int			error(const char *str);
int			prepare_shell(t_shell *data, t_env *env);
int			is_directory(const char *path);
int			check_pipe_syntax(char *input, t_env *env);
int			fork_process(t_pipe_data *pipe_data, t_command **command);
int			count_tokens(char *input, const char *delimiters);
int			check_cmd(t_command **command, t_shell data, t_env *env);
int			execute_command(t_command **command, t_env *env);
int			handle_pipe_cmd(t_command **commands, t_shell data,
				t_env *env, int num_commands);
int			exit_cmd(t_command **command, t_shell data, t_env *env);
int			check_redirection_syntax(char *input, t_env *env);
int			check_command_path(t_command **command, t_env *env, char **path);
int			child_process(t_pipe_data *pipe_data);
int			parse_key_value(const char *str, char **key, char **value);
int			execute_cprocess(t_command **command, t_shell *data, t_env *env);
char		*process_quotes(t_lex *lex);
char		**lexing(t_shell *data, t_env *env);
char		*process_dollar(t_lex *lex, t_env *env);
char		*ft_strtok(char *str, const char *delim);
char		*add_tokens(char *ptr, char *current_token);
char		*get_shell_pid(void);
char		*read_heredoc(const char *delimiter, t_env *env);
char		**get_full_path(t_env *env);
char		*find_path(t_command *cmd, t_env *env);
char		*process_char(t_lex *lex, const char *del, t_env *env);
char		*handle_dollar(t_lex *lex, t_env *env, bool in_double_quotes);
char		*get_env_value(t_env *env, char *var_name);
char		*find_path(t_command *cmd, t_env *env);
bool		is_valid_env_var(const char *str);
bool		closed_quotes(const char *input);
bool		check_op(t_lex *lex);
bool		is_bulit_in(t_command *cmd);
bool		is_valid_env_var_char(char c);
bool		is_valid_env_var(const char *str);
bool		is_delimiter(char c, const char *delim);
bool		check_newline(t_command command, int *i);
bool		echo_newline_char(char *args);
void		free_tokens(t_shell *data);
void		free_command(t_command *cmd);
void		handle_pipe(t_lex *lex);
void		handle_outred(t_lex *lex);
void		handle_outapp(t_lex *lex);
void		handle_inputred(t_lex *lex);
void		handle_heredoc(t_lex *lex);
void		handle_op(t_lex *lex);
void		print_syntax_error(char *unexpected, t_env *env);
void		env_cmd(t_command command, t_env *env, bool is_export);
void		pwd_cmd(t_command command);
void		unset_cmd(t_command *command, t_env **env);
void		export_cmd(t_command *command, t_env **env, int *status);
void		print_syntax_error(char *unexpected, t_env *env);
void		execute_commands(t_command **commands, t_shell data, t_env *env,
				int num_commands);
void		handle_redirection(t_command **command, t_env *env);
void		path_error(t_command **command, t_shell *data, t_env *env);
void		prepare_arguments(t_command *command, char ***argv);
void		print_env(t_env *env, bool is_export);
void		remove_env_variable(char *var, t_env **env);
void		preprocess_heredocs(t_command **commands, t_env *env,
				int num_commands);
void		sort_export(t_command cmd, t_env *env);
void		free_redirection(t_redirection *redir);
void		free_command_redirections(t_command *command);
void		free_heredoc_content(t_command *command);
void		free_env_list(t_env *env);
void		create_pipe(int *fd);
void		wait_for_processes(int num_commands, t_env *env,
				t_pipe_data *pipe_data);
void		handle_heredoc_redirection(t_redirection *redir);
void		free_array(char **array);
void		process_redirection(t_redirection *redir, t_env *env);
void		prepare_arguments(t_command *command, char ***argv);
void		swap_env_nodes(t_env *a, t_env *b);
void		sort_export(t_command cmd, t_env *env);
void		update_env_node(t_env *node, char *value);
void		add_env_node(t_env **env, char *key, char *value);
void		update_or_add_env_node(char *key, char *value, t_env **env);
void		add_to_list(t_env **head, t_env *new_node);
void		add_redirection(t_command *command, char *filename, int type);
void		free_heredoc(t_redirection *new_redir);
void		add_redirection_to_command(t_command *command,
				t_redirection *new_redir);
void		par_sig_handler(int sig);
void		child_sig_c(int sig);
void		set_signal(int mode);
void		heredoc_sig_handler(int sig);
void		handle_signals(t_env *env);
void		just_free(t_command **commands);
void		execute_user_commands(t_shell *data, t_env *env);
void		cleanup_after_execution(t_shell *data,
				t_command **commands, int num_commands, t_env *env);
char		*read_heredoc_loop(char *buffer, const char *delimiter, t_env *env);
char		*expand_variable(char *start, t_env *env, size_t *i);
char		*process_line(t_buffer *buf, char *line, t_env *env);
char		*handle_heredoc_dollar(char *line, t_env *env);
char		*initialize_buffer(char *buffer, size_t *size,
				size_t *buffer_capacity);
char		*append_char(char *buffer, char c, size_t *buffer_size,
				size_t *buffer_capacity);
char		*ft_strjoin_free(char *s1, char *s2);
char		*get_var_name(char *start, size_t *i);
void		just_free(t_command **commands);
void		free_heredocs(t_command **commands, int num_commands);
void		free_exit(t_command **commands, t_shell data, t_env *env);
void		handle_redirection_fork(t_command **command,
				t_env *env, t_shell *data);
void		free_split_array(char **array);
void		cleanup_after_null_tokens(t_shell *data, t_env *env);
char		*handle_special_dollar(t_lex *lex, t_env *env, bool *free_var);
char		*handle_numeric_dollar(t_lex *lex);
char		*handle_alnum_dollar(t_lex *lex, t_env *env);
char		*get_var_value(t_lex *lex, t_env *env, bool *free_var);
char		*create_new_token(char *current_token, char *var_value,
				bool free_var);
char		*remove_extra_spaces(char *str);
char		*expand_and_append(char *buffer, char *expanded_line,
				size_t *buffer_size, size_t *buffer_capacity);
#endif
