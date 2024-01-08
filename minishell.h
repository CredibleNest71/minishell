#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

struct s_command {
	char				*cmd;
	char				**args;
	int					arg_num;
	char				*nexus;
	struct s_command 	*next;
}	typedef t_command;

#endif
