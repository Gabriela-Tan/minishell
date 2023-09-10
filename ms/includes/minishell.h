/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:26:18 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/10 09:34:47 by gabriela         ###   ########.fr       */
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

# define BUFFER_SIZE 1024
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
void	ft_sync_environ(int i, char *str, t_ms *ms);
char	**ft_copy_environ(void);

// main function
// (core_main.c)
int		main(void);

// handling input
// (core_handle_input.c)
void	ft_handle_input(char *input, t_ms *ms, char *prompt);
void	ft_lexer(char **tokens, t_ms *ms);
void	ft_parse_input_string(const char *in_str, t_ms *ms);

// utils
void	free_array(char **array);
int		ft_check_builtin(char *cmd);
int		ft_get_command_count(t_cmd *cmd_head);

/* lexer */

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

/* parser */

//processing input string
// (pars_input_string.c)
char	*ft_transform_for_lexer(const char *in_str);

/* executing */

// handling environment variables
// (ex_env_replace.c)
void	ft_handle_quoted_env_vars(t_ms *ms);
void	ft_handle_unquoted_env_vars(t_ms *ms);
int		ft_find_next_env_var(char *token, int start, int *j);
char	*ft_replace_env_var(char *token);

/* builtins */



/* signals */



/* error */

#endif