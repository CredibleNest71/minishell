
#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"

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

//RETURNS:
// 1 = all good
// 0 = not ended
// -1 = error
int	check_heredoc_fin(char *str)
{
	int		j;
	int		i;
	char	*del;

	i = 2;
	j = 0;
	skip_white_space(str, &i);
	skip_chars(&str[i], &j);
	if (!str[i])
		return (write(2, "ERROR CHECKING HEREDOC: missing delimiter\n", 24), -1);
	del = ft_strndup(&str[i], j);
	printf("::check_heredoc::delimiter:%s\n", del);
	if (!del)
		return (write(2, "ERROR CHECKING HEREDOC\n", 24), -1);
	if (ft_strnstr(str + i + j, del, 10000))
		return (free(del), 1);
	else
		return (free(del), 0);
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
		if (!strncmp(&input[i], "<<", 2) && fin > 0)
			if (check_heredoc_fin(&input[i]) <= 0)
				return (check_heredoc_fin(&input[i]));
		i++;
	}
	return (fin > 0 ? 1 : 0);
}

int main(void)
{
	char    	*input;
	char		*temp;
	char		*temp2;
	t_token		*parsed;
	t_command	*cmds;
	int			finished;

	finished = 0;
	input = ft_strdup("");
	printf("Enter commands:");
	while (!finished)
	{
		temp = input;
		temp2 = readline(">");
		input = ft_strjoin(input, temp2);
		free(temp);
		free(temp2);
		finished = check_fin(input);
		if (finished < 0)
			return (write(2, "ERROR\n", 7));
	}
	parsed = parse(input); //
	cmds = transform(parsed);//
	print_cmds(cmds);
	delete_command_list(cmds);
	free(input);
	return (0);
}
