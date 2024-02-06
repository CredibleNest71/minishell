NAME = minishell

CC = cc

FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = src/

MAIN_DIR = main/

PARSER_DIR = parser/

EXEC_DIR = execution/

BUILT_INS = built-ins/

SRCS = ${SRC_DIR}${EXEC_DIR}exec.c\
			${SRC_DIR}${EXEC_DIR}pathfinder.c\
			${SRC_DIR}${EXEC_DIR}redirection.c\
			${SRC_DIR}${EXEC_DIR}simple_execution.c\
			${SRC_DIR}${EXEC_DIR}built_in_list.c\
			${SRC_DIR}${EXEC_DIR}error_handlers.c\
\
			${SRC_DIR}${BUILT_INS}cd.c\
			${SRC_DIR}${BUILT_INS}echo.c\
			${SRC_DIR}${BUILT_INS}export.c\
			${SRC_DIR}${BUILT_INS}pwd.c\

OBJS := $(SRCS:%.c=%.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I./

all: $(NAME)

$(NAME): $(OBJS)
	cd libft && $(MAKE) && $(MAKE) bonus
	cc $(FLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

clean:
	cd libft && $(MAKE) fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re