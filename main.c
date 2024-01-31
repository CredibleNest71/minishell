# include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_bigshell	shell_struct;
	char		*lineread;

	lineread = NULL;
	shell_struct.env = env;
		while (1)
	    {
		    lineread = readline("tinyshell: ");
		    commands = parse(stdin);
			if (commands.)
		    exec(commands);
	    }
	    return (0);
}
