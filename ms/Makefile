NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L/usr/local/opt/readline/lib

LIB_PATH = includes/libft/libft.a
INC = -I ./includes/\
      -I ./includes/libft/\
      -I /usr/local/opt/readline/include

SRC_PATH = src/
SRC = core_init.c \
      core_main.c \
      core_prompt.c \
      ex_cmd.c \
      lex_process_tokens.c \
      ex_redir_builtins.c \
      ex_redir_io.c \
      lex_cmd_arg_to_tokens.c \
      lex_cmd_type.c \
      ex_redirections.c \
      pars_env_replace.c \
      pars_replace_symbols.c \
      utils.c \
      utils_free.c \
      builtin_cd.c \
      builtin_echo.c \
      builtin_echo2.c \
      buildin_pwd.c \
      buildin_env.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

OBJ_LINK = .relink_obj_link_check

all: $(LIB_PATH) $(NAME)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIB_PATH):
	@make -sC includes/libft/

$(NAME): $(OBJ_LINK)

$(OBJ_LINK): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -lreadline -o $(NAME) $(OBJS) $(LIB_PATH) $(INC)
	@touch $(OBJ_LINK)
	@echo "minishell is good to go!"
	@echo "run ./minishell"

clean:
	@rm -Rf $(OBJ_PATH)
	@rm -f $(OBJ_LINK)
	@make clean -sC includes/libft/
	@echo "Cleaning successful"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIB_PATH)
	@echo "All generated files are deleted"

re: fclean all
	@echo "Remake completed"

.PHONY: all re clean fclean
