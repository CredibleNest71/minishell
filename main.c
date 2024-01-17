# include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_command	*commands;
    char prompt[] = "tinyShell>> "; // ?
	char	*lineread;

	lineread = NULL;
	commands->env = env;
	while (1)
    {
		
        //printf("%s", prompt); 
		lineread = readline("tinyshell"); // free lineread
		/* if (!lineread) // protection?
			return (); */
		commands = parse(stdin);	//PARSE
		exec(commands);			//DO
    }
    return (0);
}