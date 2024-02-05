# include "../../minishell.h"

int main(int argc, char **argv, char **env)
{
	t_bigshell	bigshell;
	char		*lineread;

	lineread = NULL;
	bigshell.env = env;
	bigshell.built_ins = built_in_list();
		while (1)
	    {
		    lineread = readline("tinyshell: ");
		    bigshell.commands = parse(stdin);
			store_restore_fds(1); //will store stdin & stdout
			if (bigshell.num_cmd == 1)
				simple_exec(bigshell);
			else
				complex_exec(bigshell);
	    }
	    return (0);
}
