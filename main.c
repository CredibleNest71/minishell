# include "minishell.h"

int main(void)
{
	t_command	*commands;
    char prompt[] = "tinyShell>> ";

    while (1)
    {
        printf("%s", prompt);

		commands = parse(stdin)	//PARSE
		exec(commands);			//DO
    }
    return (0);
}   