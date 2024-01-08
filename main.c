# include "minishell.h"

int main(void)
{
    char prompt[] = "tinyShell>> ";
    while (1)
    {
        printf("%s", prompt);

		commands = parse(stdin)	//PARSE
		exec(commands);			//DO
    }
    return (0);
}   