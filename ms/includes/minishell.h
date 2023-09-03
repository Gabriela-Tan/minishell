/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 08:26:18 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:28:09 by gabriela         ###   ########.fr       */
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

# define UNUSED(x) (void)(x)

typedef struct s_cmd
{
	char *cmd;
	char **arg;
	struct s_cmd *next;
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
}	t_env;

extern char	**environ;

/* testing */
/* testing lex_handle_str */
/*
void	ft_test_lexer(char **tokens, t_env *env);
void test_parse_input_string(const char *input);
void test_handle_quotes(char **tokens);
int main(void);
*/

/* testing lex_redirections */
/*
void test_input_redirs(void);
void test_output_redirs(void);
void test_is_not_redir(void);
void test_array_wo_redirs(void);
void test_process_redirs(void);
int main(void);
*/

/* testing arg tokens */
/*
int main(void);
*/

/* utils */
void	free_array(char **array);
int	ft_check_builtin(char *cmd);

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

//tokenizing commands
// (lex_cmd_tokens.c)
void	cmd_to_tokens(char **tokens, t_env *env);
int		count_cmd(char **tokens);
t_cmd	*create_new_node(int *i, char **tokens);

//tokenizing arguments
int		count_arg(char **tokens, int i);
void	add_cmd(t_cmd **head, char *cmd, char **arg);
void	tokenize_cmd_and_args(char **tokens, t_env *env);

//command path
// (lex_cmd_path.c)






/* parsing */



/* executing */



/* builtins */



/* signals */



/* error */

#endif