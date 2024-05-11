NAME = minishell

CC = cc

FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = src/

LIB_DIR = libft

MAIN_DIR = main/

PARSER_DIR = parser/

EXEC_DIR = execution/

BUILT_INS = built-ins/

EXPORT = export/

CD = cd/

ECHO = echo/

ENV = env/

EXIT = exit/

PWD = pwd/

UNSET = unset/

BUILT-IN-LIST = execution/built-in-list/

HELPER = execution/helper_functions/

HEREDOC = execution/heredoc/

REDIR = execution/redirection/

SRCS = ${SRC_DIR}${BUILT-IN-LIST}built_in_list.c\
			${SRC_DIR}${BUILT-IN-LIST}put_built_in.c\
\
			${SRC_DIR}${EXEC_DIR}close_fds_child.c\
			${SRC_DIR}${EXEC_DIR}complex_exec.c\
			${SRC_DIR}${EXEC_DIR}env_list.c\
			${SRC_DIR}${EXEC_DIR}error_handlers.c\
\
			${SRC_DIR}${HELPER}helper_functions.c\
			${SRC_DIR}${HELPER}helper_functions2.c\
\
			${SRC_DIR}${HEREDOC}heredoc.c\
			${SRC_DIR}${HEREDOC}heredoc_tmpfile.c\
			${SRC_DIR}${HEREDOC}heredoc_close_fd.c\
\
			${SRC_DIR}${EXEC_DIR}pathfinder.c\
\
			${SRC_DIR}${REDIR}redirection.c\
			${SRC_DIR}${REDIR}redirection2.c\
\
			${SRC_DIR}${EXEC_DIR}simple_execution.c\
\
			${SRC_DIR}${BUILT_INS}${CD}cd.c\
			${SRC_DIR}${BUILT_INS}${CD}cd_overwrite.c\
			${SRC_DIR}${BUILT_INS}${ECHO}echo.c\
			${SRC_DIR}${BUILT_INS}${ENV}env.c\
			${SRC_DIR}${BUILT_INS}${EXIT}exit.c\
			${SRC_DIR}${BUILT_INS}${PWD}pwd.c\
			${SRC_DIR}${BUILT_INS}${UNSET}unset.c\
			${SRC_DIR}${BUILT_INS}${EXPORT}export.c\
			${SRC_DIR}${BUILT_INS}${EXPORT}export_sort.c\
			${SRC_DIR}${BUILT_INS}${EXPORT}export_print_copy.c\
			${SRC_DIR}${BUILT_INS}${EXPORT}export_check_var.c\
			${SRC_DIR}${BUILT_INS}${EXPORT}export_check_var_exists.c\
\
			${SRC_DIR}${PARSER_DIR}parse.c\
			${SRC_DIR}${PARSER_DIR}commander.c\
			${SRC_DIR}${PARSER_DIR}expansion_alt.c\
			${SRC_DIR}${PARSER_DIR}expansion_routine1.c\
			${SRC_DIR}${PARSER_DIR}expansion_routine2.c\
			${SRC_DIR}${PARSER_DIR}expansion_routine3.c\
			${SRC_DIR}${PARSER_DIR}extras.c\
			${SRC_DIR}${PARSER_DIR}extras2.c\
			${SRC_DIR}${PARSER_DIR}tokenv1.c\
			${SRC_DIR}${PARSER_DIR}tokenextras.c\
			${SRC_DIR}${PARSER_DIR}tokenextras2.c\
			${SRC_DIR}${PARSER_DIR}syntax.c\
\
\
			${SRC_DIR}${MAIN_DIR}minimain.c\
			${SRC_DIR}${MAIN_DIR}sig.c\
			${SRC_DIR}${MAIN_DIR}mainextra.c\
\
			${SRC_DIR}${PARSER_DIR}NOT_IN_FINAL.c\

OBJS := $(SRCS:%.c=%.o)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I./

all: $(NAME)

$(NAME): $(OBJS)
	cd $(LIB_DIR) && $(MAKE) && $(MAKE) bonus
	cc $(FLAGS) $(OBJS) -lreadline ./$(LIB_DIR)/libft.a -o $(NAME)

valgrind : $(NAME)
	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./minishell

clean:
	cd $(LIB_DIR) && $(MAKE) fclean
	rm -f $(OBJS)

nice: all clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind