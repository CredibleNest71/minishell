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
		for (int i = 0; i < temp_cmd->arg_num; i++)
			printf("\nchars: %s", temp_cmd->args_exec[i]);
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

void	set_char_array(t_command *final)
{
	t_token		*temparg;
	int			i;

	final->args_exec = (char **) ft_calloc (sizeof(char *), final->arg_num + 1);
	temparg = final->args;
	i = 0;
	while (temparg)
	{
		final->args_exec[i++] = ft_strdup(temparg->str);
		temparg = temparg->next;
	}
	return ;
}

void	set_all_char_arrays(t_command *final)
{
	t_command	*temp;

	temp = final;
	while (temp)
	{
		set_char_array(temp);
		temp = temp->next;
	}
	return ;
}

/*
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
*/
t_command	*parse(char *input, t_bigshell *data)
{
	t_token		**tokens;
	t_command	**cmds;

	if (!input)
		return (NULL);
	tokens = tokenmaker(input);
	tokens = expander(tokens, data);
	cmds = commands_finalized(tokens);
	set_counts(*cmds, data);
	set_all_char_arrays(*cmds);
	return (*cmds);
}