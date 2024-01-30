#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

enum type {
	CMD = 0,
	ARG,
	PATH,
	NEX,
	DIR,
} typedef e_type;

struct s_token {
	char 	*str;
	int		type;
} typedef t_token;

struct s_command {
	void				*input;
	void				*output;
	t_token				*extra;
	t_token				*cmd;
	char				**arg;
	t_token				**args;
	int					arg_num;
	t_token				*nexus;
	struct s_command 	*next;
}	typedef t_command;


#endif