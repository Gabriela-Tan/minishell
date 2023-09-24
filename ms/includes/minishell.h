/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:26:18 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/24 12:24:21 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>

# define TOKEN_DELIMITER 29
# define FLAGS_APPEND (O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC)
# define FLAGS_OVERWRITE (O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC)
# define FLAGS_READ (O_RDONLY | O_CLOEXEC)
# define FILE_MODE 0777

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_ms
{
	t_cmd	*cmd_head;
	int		i_last_cmd;
	int		in_fd;
	int		out_fd;
	char	*delim;
	int		saved_stdin;
	int		saved_stdout;
	char	**env;
	int		exit_status;
	char	**tokens;
}	t_ms;

extern char	**environ;

/* core functionality */

// initializations
// (core_init.c)
void	ft_init(t_ms *ms);
void	ft_reset(t_ms *ms);

// handling the prompt
// (core_prompt.c)
void	ft_change_prompt(t_ms *ms);
void	ft_sync_env(int i, char *str, t_ms *ms);
char	**ft_copy_environ(void);

// main function

// (core_handle_input.c)
void	ft_handle_input(char *input, t_ms *ms, char *prompt);
void	ft_lex_and_parse_input_string(const char *in_str, t_ms *ms);
void	ft_executor(t_ms *ms);
int		main(void);

// utils
int		ft_check_builtin(char *cmd);
int		ft_get_command_count(t_cmd *cmd_head);
void	ft_command_not_found(t_cmd *current);

// utils_free
// (utils_free.c)
void	free_array(char **array);
void	free_cmd_list(t_cmd *head);
void	free_and_exit(int status, t_ms *ms);

/* lex and parse input string */

//processing and handling redirections
// (lex_handle_redirs.c)
void	input_redirs(char **tokens, t_ms *ms, char **last_ll, char **last_l);
void	output_redirs(char **tokens, t_ms *ms, char **last_gg, char **last_g);
int		is_not_redir(char *tokens);
char	**array_wo_redirs(char **old_array, int *count, int i, int j);
void	process_redirs(char **tokens, t_ms *ms);

//tokenizing commands and arguments
// (lex_cmd_arg_to_tokens.c)
int		count_cmd(char **tokens);
void	add_cmd(t_cmd **head, char *cmd, char **arg);
t_cmd	*create_new_cmd_node(char **tokens, int *i, int total_arg);
int		count_arg(char **tokens, int i);
void	tokenize_cmd_and_args(char **tokens, t_ms *ms);

//checking command type
// (lex_cmd_type.c)
void	ft_check_cmd_type(t_ms *ms);
int		ft_check_path_exec(char *cmd);
int		ft_search_for_exec(char **paths, char *cmd);
char	*ft_search_and_get_path(char **paths, char *cmd, int i);
char	*ft_return_path(char *cmd);

//processing input string
// (pars_handle_string.c)
char	*ft_transform_for_lexer(const char *in_str);

// handling environment variables
// (pars_env_replace.c)
void	ft_handle_quoted_env_vars(t_ms *ms);
void	ft_handle_unquoted_env_vars(t_ms *ms);
int		ft_find_next_env_var(char *token, int start, int *j);
char	*ft_replace_env_var(char *token);
void	handle_quotes(char **arg);

// Replace special symbols
// (pars_replace_symbols.c)
char	*ft_transform_for_lexer(const char *in_str);
void	ft_replace_symbols(t_ms *ms);
char	*ft_replace_exit(char *token, int exit_status, int i, int replaced);
char	*ft_replace_home_path(char *token, int i, char *home_path);

/* executing */

// handle input and output redirections
// (ex_handle_io.c)
void	ft_restore_input_output(t_ms *ms);
void	ft_handle_input_redirection(t_ms *ms);
void	ft_handle_output_redirection(t_ms *ms, t_cmd *current);

// execute commands that are piped together
// (ex_cmd_in_pipe.c)
void	ft_handle_child_process(t_cmd *current, int fd[], t_ms *ms);
void	ft_handle_parent_process(int fd[], pid_t pid, t_ms *ms);
void	ft_execute_cmd_in_pipe(t_ms *ms, t_cmd *current);

// execute commands directly or forked
// ex_redir_builtins.c
void	ft_heredoc(char *delim, int pid);
void	ft_error(void);
void	ft_execute_builtin_directly(t_cmd *current, t_ms *ms);
void	ft_execute_forked_builtin(t_cmd *current, t_ms *ms);

/* builtins */

// cd
// (builtin_cd.c)
int		ft_command_counting(t_cmd *current);
void	ft_cd_as_forked(t_cmd *current, t_ms *ms);
int		ft_cd_directly(t_cmd *current, t_ms *ms);
int		ft_move_dir(char *dest, char *old_pwd, char *cwd, t_ms *ms);
void	ft_update_or_add_env(char *var, char *value, t_ms *ms);

/* signals */




#endif