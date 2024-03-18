#include "../../minishell.h"
#include "parse.h"

void	print_cmds(t_command *cmd, t_bigshell *data)
{
	if (!cmd)
	{
		write(2, "(NO COMMANDS)\n", 8);
		return ;
	}
	t_command *temp_cmd = cmd;
	printf("\n==========================================\n");
	printf("NUMBER OF COMMANDS: %d\n", data->num_cmd);
	for (;temp_cmd; temp_cmd = temp_cmd->next)
	{
		printf("\n==========================================");
		if (temp_cmd->cmd)
			printf("\nCOMMAND(%d):		%s",temp_cmd->arg_num, temp_cmd->cmd->str);
		for (t_token *curr = temp_cmd->args;curr; curr = curr->next)
			printf("\n	ARG:		%s", curr->str);
		for (t_token *curr = temp_cmd->input;curr; curr = curr->next)
		{
			printf("\nIN:			%s", curr->str);
			if (curr->type == (e_type) HEREDOC)
				printf("\n	Delimiter: 	%s", curr->delimiter);
		}
		for (t_token *curr = temp_cmd->output;curr; curr = curr->next)
		{
			if (curr->type == (e_type) APP)
				printf("\nAPP:			%s", curr->str);
			else
				printf("\nOUT:			%s", curr->str);
		}
		printf("\n==========================================\n");
	}
}

static int set_counts(t_command *cmd, t_bigshell *data)
{
	t_command	*temp;
	t_token		*arg;
	int	i;
	int j;

	j = 0;
	temp = cmd;
	while (temp)
	{
		i = 0;
		arg = temp->args;
		while (arg)
		{
			i++;
			arg = arg->next;
		}
		temp->arg_num = i;
		temp = temp->next;
		j++;
	}
	if (data)
		data->num_cmd = j;
	return (j);
}

t_command	*parse(char *input, t_bigshell *data)
{
	t_token		*parsed;
	t_command	*final;

	//input = prexpand(input, data);
	if (!input)
		return (NULL);
	parsed = parse_tokens(input);
	if (!parsed)
		return (write(2, "ERROR in::parse::parsed\n", 25), NULL);
	if (data && parsed->type == (e_type) HEREDOC)
	{
		data->heredoc = parsed;
		parsed = parsed->next;
	}
	final = transform(parsed, data);
	if (!final)
		return (write(2, "ERROR in::parse::final\n", 24), NULL);
	set_counts(final, data);
	return (final);
}
