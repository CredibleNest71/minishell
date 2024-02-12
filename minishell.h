#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum type {
	CMD = 0,
	ARG,
	PIPE,
	IN,
	OUT,
	APP,
	HEREDOC,
}	 e_type;

typedef struct s_token {
	char 			*str;
	int				type;
	char			*dir;
	struct s_token	*next;
}	 t_token;

typedef struct s_command {
	t_token				*input;		//<
	t_token				*output;	//>
	t_token				*cmd;		//command
	t_token				**args;		//arguments
	int					arg_num;
	t_token				*nexus;		//PIPE?
}	 t_command;

typedef struct	s_bigshell
{
	t_command	**command;
	int			exit_stat;
	char		**env;
}	 t_bigshell;

#endif
