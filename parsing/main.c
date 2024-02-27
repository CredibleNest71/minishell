
#include "../minishell.h"
#include "parse.h"
#include "../libft/libft.h"

void	print_cmds(t_command *cmd)
{
	if (!cmd)
	{
		write(2, "(NULL)\n", 8);
		return ;
	}
	t_command *temp_cmd = cmd;
	for (;temp_cmd; temp_cmd = temp_cmd->next)
	{
		printf("\n==========================================");
		printf("\nCOMMAND:		%s", temp_cmd->cmd->str);
		for (t_token *curr = temp_cmd->args;curr; curr = curr->next)
			printf("\n	ARG:		%s", curr->str);
		for (t_token *curr = temp_cmd->input;curr; curr = curr->next)
			printf("\nIN:			%s", curr->str);
		for (t_token *curr = temp_cmd->output;curr; curr = curr->next)
			printf("\nOUT:			%s", curr->str);
		for (t_token *curr = temp_cmd->append;curr; curr = curr->next)
			printf("\nAPP:			%s", curr->str);
		for (t_token *curr = temp_cmd->heredoc;curr; curr = curr->next)
			printf("\nHere:			%s", curr->str);
		printf("\n==========================================");
	}
}

static int check_fin(char *input)
{
	int		i;
	int 	fin;
	char	c;
	i = 0;
	fin = 1;
	c = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			fin *= -1;
			c = 0;
		}
		else if (!c && (input[i] == '\"' || input[i] == '\''))
		{
			fin *= -1;
			c = input[i];
		}
		i++;
	}
	return (fin > 0 ? 0 : 1);
}
int main(void)
{
	char    	*input;
	char		*temp;
	char		*temp2;
	t_token		*parsed;
	t_command	*cmds;
	int			unfinished;

	unfinished = 1;
	input = ft_strdup("");
	printf("Enter commands:");
	while (unfinished)
	{
		temp = input;
		temp2 = readline(">");
		input = ft_strjoin(input, temp2);
		free(temp);
		free(temp2);
		unfinished = check_fin(input);
	}
	parsed = parse(input);
	cmds = transform(parsed);
	print_cmds(cmds);
	delete_command_list(cmds);
	free(input);
	return (0);
}
