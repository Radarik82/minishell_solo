/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dprudnik <dprudnik@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:43:33 by ariazano          #+#    #+#             */
/*   Updated: 2026/02/16 21:50:01 by dprudnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

//signal variable
extern int	g_signal_received;

// COLORS
# define GREEN	"\033[0;32m"
# define RED	"\033[1;31m"
# define GREY	"\033[0;90m"
# define CYAN	"\033[1;96m"
# define YELLOW	"\033[0;33m"
# define BLUE	"\033[1;34m"
# define RESET	"\033[0m"

// types of token |  &  ;  <  >  (  )  $  `  \  "  '  <space>  <tab>  <newline>
typedef enum e_token_type
{
	T_NEWLINE,
	T_SPACE,
	T_DOLLAR,
	T_AMPER,
	T_TAB,
	T_APPEND,
	T_PIPE,
	T_OR,
	T_AND,
	T_DELIM,
	T_LPAR,
	T_RPAR,
//	T_WORD = 1,
//	T_RED_INP,
//	T_RED_OUT,
//	T_THREE_IN,
//	T_THREE_OUT,
//	T_IN_OUT,
}			t_token_type;

/* Shell context structure */
typedef struct	s_shell
{
	char		**env;
	int			exit_status;
}				t_shell;

/* Command structure */
typedef struct	s_cmd
{
	char		**args;
	int			input_count;
	char		**input_files;   // Array of input files
	int			output_count;
	char		**output_files;  // Array of output files
	int			*append_flags;   // Array of append flags for each output
}				t_cmd;

/* Pipeline structure */
typedef struct	s_pipeline
{
	t_cmd		**cmds;
	int			cmd_count;
}				t_pipeline;

typedef struct	s_exec
{
	t_pipeline	*p;
	t_shell		*shell;
	int			i;
	int			prev_fd;
	int			pipefd[2];
}				t_exec;



/*
typedef struct	s_data
{
	int		argc;
	char	**argv;
	char	*env;
}				t_data;

typedef struct	s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;
*/

/* pipe_setup.c*/

/* pipe_utils.c*/
int		create_pipe_fds(int *fd);
void	close_pipe_fds(int *fd);
void	setup_input_pipe(int *fd);
void	setup_output_pipe(int *fd);
void	close_unused_pipes(int *prev_fd, int *curr_fd);

/* builtin_cmds.c*/
int		exec_echo(char **args);
int		is_valid_n_flag(char *arg);
int		exec_cd(char *path);
int		exec_exit(t_pipeline *p, t_cmd *cmd, t_shell *shell);
int		exec_env(t_shell *shell);

/* builtin_cmds_2.c*/


/* builtin_utils.c*/
int		is_builtin(char *arg);
int		execute_builtin(t_pipeline *p, t_cmd *cmd, t_shell *shell);
// int		execute_builtin_with_redirection(t_cmd *cmd);


/* signals.c */
void	setup_signals(void);
void	handle_sigint(int sig);
void	setup_tmp_signals(void);

/* env_mod_utils.c*/
char	*create_env_var(char *key, char *value);
int		find_env_index(char **env, char *key);
int		add_env_var(char ***env, char *new_var);
int		update_env(char ***env, char *key, char *value);

/* env_utils.c */
int		env_size(char **env);
char	**copy_env(char **env);
void	free_env(char **env);
char	*get_env_var(char *name, char **env);

/* errors.c */
void	free_and_error(t_pipeline *pipeline, t_shell *shell, char *msg, int code);
void	print_error(char *msg);
void	exit_error(char *msg, int code);

/* find_path.c */
char	*find_command(char *cmd, char **env);
char	*get_path_env(char **env);
char	**split_path(char *path_env);
int		is_executable(char *path);
char	*join_path_cmd(char *dir, char *cmd);

/* redirections.c*/
int		handle_input_redirection(char *infile);
int		handle_output_redirection(const char *outfile, int append);
int		save_std_fds(int *saved_stdin, int *saved_stdout);
void	restore_std_fds(int saved_stdin, int saved_stdout);

/* execute_pipes.c*/
void	run_pipeline(t_pipeline *pipeline, t_shell *shell);
int		execute_multi_cmds(t_pipeline *p, t_shell *shell);
// void		run_pipeline_recursive(t_pipeline *pipeline, t_shell *shell, int current_index, int *input_fd);

/* execute.c */
int		execute_command(char **args, t_shell *shell);
int		fork_and_exec(char **args, t_shell *shell);
void	execute_child(char **args, char **env);
int		is_absolute_path(char *str);
int		is_relative_path(char *str);

/* string_utils.c */
void	free_array(char **arr);
int		array_len(char **arr);
char	*ft_strjoin_free(char *s1, char *s2);

/* parse_pipeline.c*/
int			is_empty_segment(char *segment);
t_cmd		*create_cmd(char **args);
void		free_cmd(t_cmd *cmd);
t_pipeline	*create_pipeline(char **segments);
void		free_pipeline(t_pipeline *pipeline);
t_cmd		*parse_one_segment(char *segment);
t_pipeline	*alloc_pipeline(int count);

/* pipeline_utils.c*/


/* split_pipes_utils.c*/
// char	**split_by_pipes(char *input);

/* split_pipes.c */
int		is_pipe(char c);
int		count_pipes(char *str);
int		find_pipe_pos(char *input, int start);
char	*extract_segment(char *input, int start, int end);
char	*get_next_segment(char *input, int *pos);
char	**split_by_pipes(char *input);

/* tokenize.c */
char	**tokenize_input(char *input);
int		count_words(char *str);
char	*extract_word(char *str, int start, int len);
int		get_word_len(char *str, int start);
int		is_space(char c);

#endif
