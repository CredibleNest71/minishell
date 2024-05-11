CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
NAME		=	get_next_line.a
SRC			=	get_next_line.c get_next_line_utils.c
OBJ			=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
				ar -crs $(NAME) $(OBJ)

clean:
				rm -f $(OBJ)

fclean: clean
				rm -f $(NAME)

re: 			fclean all

.PHONY:		all clean fclean re 