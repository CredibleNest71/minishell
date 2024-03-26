CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	libft.a
SRC			=	ft_isalpha.c ft_toupper.c ft_isdigit.c ft_tolower.c ft_isalnum.c ft_isascii.c ft_strchr.c\
				ft_isprint.c ft_strrchr.c ft_strlen.c ft_strncmp.c ft_memset.c ft_memchr.c ft_bzero.c\
				ft_memcmp.c ft_memcpy.c ft_strnstr.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_atoi.c\
				ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
				ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJ			=	$(SRC:.c=.o)
BONUS		=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c\
				ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c 
BONUS_OBJ	=	$(BONUS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
				ar -crs $(NAME) $(OBJ)

clean:
				rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
				rm -f $(NAME)

re: 			fclean all

bonus:		$(BONUS) $(BONUS_OBJ) $(NAME)
				ar -rc $(NAME) $(OBJ) $(BONUS_OBJ)

.PHONY:		all clean fclean re bonus