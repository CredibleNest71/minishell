CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	parse

all:		$(NAME)

$(NAME):
			$(CC)  ../libft/ft_split.c ../libft/ft_strncmp.c ../libft/ft_strdup.c ../libft/ft_strlen.c parse.c token.c expander.c -o $(NAME)

fclean:
				rm -f $(NAME)

re: 			fclean all

bonus:		$(BONUS) $(BONUS_OBJ) $(NAME)
				ar -rc $(NAME) $(OBJ) $(BONUS_OBJ)

.PHONY:		all clean fclean re bonus