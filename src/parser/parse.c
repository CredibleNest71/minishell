#include "../../minishell.h"
#include "parse.h"

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
		{
			printf("\nIN:			%s", curr->str);
			if (curr->type == (e_type) HEREDOC)
				printf("\nDelimiter: %s", curr->delimiter);
		}
		for (t_token *curr = temp_cmd->output;curr; curr = curr->next)
			printf("\nOUT:			%s", curr->str);
		for (t_token *curr = temp_cmd->append;curr; curr = curr->next)
			printf("\nAPP:			%s", curr->str);
		for (t_token *curr = temp_cmd->heredoc;curr; curr = curr->next)
			printf("\nHere:			%s", curr->str);
		printf("\n==========================================");
	}
}

t_command	*parse(char *input, t_bigshell *data)
{
	t_token		*parsed;
	t_command	*final;

	parsed = parse_tokens(input);
	if (data && parsed->type == (e_type) HEREDOC)
		data->heredoc = parsed;
	if (!parsed)
		return (NULL);
	final = transform(parsed);
	if (!final)
		return (NULL);
	return (final);
}