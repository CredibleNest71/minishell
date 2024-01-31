# include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_bigshell	bigshell;
	char		*lineread;

	lineread = NULL;
	bigshell.env = env;
		while (1)
	    {
		    lineread = readline("tinyshell: ");
		    bigshell.commands = parse(stdin);
			if (bigshell.commands /*->to num of cmds || if cmds == 1*/)
				simple_exec();
			else
				complex_exec(bigshell);
	    }
	    return (0);
}
