/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:26:18 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/05 15:52:54 by gabriela         ###   ########.fr       */
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

typedef struct s_env
{
	t_cmd	*cmd_head;
	int		i_cmd;
	int		in_fd;
	int		out_fd;
	char	*delim;
	int		saved_stdin;
	int		saved_stdout;
	char	**env;
	int		exit_status;
	char	**tokens;
}	t_env;

extern char	**environ;

/* testing */
int		main(void);
void	print_commands(t_cmd *head);

/* utils */
void	free_array(char **array);
int		ft_check_builtin(char *cmd);

/* init */
void	ft_init(t_env *env);

//processing input string
char	*ft_transform_for_lexer(const char *in_str);
char	**ft_handle_quotes(char **tokens);
void	ft_parse_input_string(const char *in_str, t_env *env);

/* lexer */
//lexer
// (lex_lexer.c)
void	ft_lexer(char **tokens, t_env *env);

//processing and handling redirections
// (lex_handle_redirs.c)
void	input_redirs(char **tokens, t_env *env, char **last_ll, char **last_l);
void	output_redirs(char **tokens, t_env *env, char **last_gg, char **last_g);
int		is_not_redir(char *tokens);
char	**array_wo_redirs(char **old_array, int *count, int i, int j);
void	process_redirs(char **tokens, t_env *env);

//tokenizing commands and arguments
// (lex_cmd_arg_to_tokens.c)
int		count_cmd(char **tokens);
void	add_cmd(t_cmd **head, char *cmd, char **arg);
t_cmd	*create_new_cmd_node(char **tokens, int *i, int total_arg);
int		count_arg(char **tokens, int i);
void	tokenize_cmd_and_args(char **tokens, t_env *env);

//checking command type
// (lex_cmd_type.c)
void	ft_check_cmd_type(t_env *env);
int		ft_check_path_exec(char *cmd);
int		ft_search_for_exec(char **paths, char *cmd);
char	*ft_search_and_get_path(char **paths, char *cmd, int i);
char	*ft_return_path(char *cmd);

/* parsing */



/* executing */



/* builtins */



/* signals */



/* error */

#endif