# include "minishell.h"

int main(void)
{
t_command	*commands;
	char		*lineread;
   // char prompt[] = "tinyShell>> ";
	lineread = NULL; //?
	commands.env = env;
		while (1)
	    {
		    //printf("%s", prompt);
		    lineread = readline("tinyshell: ");
		    commands = parse(stdin); //PARSE
		    exec(commands); //DO
	    }
	    return (0);
}