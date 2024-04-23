#include "../../minishell.h"
#include <stdio.h>
#include "parse.h"

void	print_cmds(t_command *cmd, t_bigshell *data)
{
	if (!cmd)
	{
		write(2, "(NO COMMANDS)\n", 15);
		return ;
	}
	t_command *temp_cmd = cmd;
	printf("\n==========================================\n");
	printf("==========================================\n");
	printf("==	NUMBER OF COMMANDS: %d\n", data->num_cmd);
	printf("==========================================\n");
	if (data->heredoc)
	{
		for (t_token *temp = (data->heredoc); temp; temp = temp->next)
			printf("==	HEREDOCS:		%s\n", temp->str);
	}
	else
		printf("=	NO HEREDOCS\n");
	printf("==========================================\n");
	for (;temp_cmd; temp_cmd = temp_cmd->next)
	{
		printf("==========================================\n");
		if (temp_cmd->cmd)
			printf("== COMMAND(%d):%s\n",temp_cmd->arg_num, temp_cmd->cmd->str);
		printf("== ");
		if (temp_cmd->prev)
			printf("== previous command: %s\n", temp_cmd->prev->cmd->str);
		for (int i = 0; i < temp_cmd->arg_num + 1; i++)
		{
			printf("[%s]", temp_cmd->args_exec[i]);
		}
		printf("\n");
		for (t_token *curr = temp_cmd->args;curr; curr = curr->next)
			printf("==	ARG:		%s\n", curr->str);
		for (t_token *curr = temp_cmd->input;curr; curr = curr->next)
		{
			if (curr->type == (e_type) IN)
				printf("==	IN:			%s\n", curr->str);
			else if (curr->type == (e_type) HEREDOC)
				printf("==	HEREDOC: 	%s\n", curr->str);
		}
		for (t_token *curr = temp_cmd->output; curr; curr = curr->next)
		{
			if (curr->type == (e_type) APP)
				printf("==	APP:			%s\n", curr->str);
			else
				printf("==	OUT:			%s\n", curr->str);
		}
	}
	printf("==========================================\n\n");
}