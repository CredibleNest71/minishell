CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	parse

all:		$(NAME)

$(NAME):
			$(CC) main.c expander.c tokenv2.c extras.c classifier.c ../libft/*.c -lreadline

fclean:
				rm -f $(NAME)

re: 			fclean all

bonus:		$(BONUS) $(BONUS_OBJ) $(NAME)
				ar -rc $(NAME) $(OBJ) $(BONUS_OBJ)

.PHONY:		all clean fclean re bonus