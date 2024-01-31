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
}	typedef e_type;

struct s_token {
	char 	*str;
	int		type;
	char	*dir;
}	typedef t_token;

struct s_command {
	t_token				*input;		//<
	t_token				*output;	//>
	t_token				*cmd;		//command
	t_token				**args;		//arguments
	int					arg_num;
	t_token				*nexus;		//PIPE?
}	typedef t_command;

#endif
