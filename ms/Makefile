NAME = minishell

# compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -L/usr/local/opt/readline/lib

LIB_PATH = includes/libft/libft.a
INC = -I ./includes/\
      -I ./includes/libft/\
      -I /usr/local/opt/readline/include

SRC_PATH = src/
SRC = init.c \
      utils.c \
      lex_handle_str.c \
      lex_redirections.c \
      lex_lexer.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))

#objects
OBJ_PATH = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(LIB_PATH) $(NAME)

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIB_PATH):
	@make -sC includes/libft/

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) -lreadline -o $(NAME) $(OBJS) $(LIB_PATH) $(INC)
	@echo "minishell is good to go!"
	@echo "run ./minishell"

clean:
	@rm -Rf $(OBJ_PATH)
	@make clean -sC includes/libft/
	@echo "Cleaning successful"

fclean: clean
	rm -f $(NAME)
	rm -f $(LIB_PATH)
	@echo "All generated files are deleted"

re: fclean all
	@echo "Remake completed"

.PHONY: all re clean fclean
