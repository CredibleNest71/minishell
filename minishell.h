#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
//# include "libft/libft.h" sacar el "//" antes de merge
# include "execution/temp_libft/libft.h"

struct s_command {
	char				*cmd;
	char				**args;
	int					arg_num; // num of cmds
	char				*nexus;
	struct s_command 	*next;

	char				**env;
}	typedef t_command;

#endif
