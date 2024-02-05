#include "../../minishell.h"


int main ()
{
	t_command	*command = (t_command *) malloc (sizeof(t_command));
	t_token 	*in = (t_token *) malloc (sizeof(t_token));
	t_token 	*out = (t_token *) malloc (sizeof(t_token));
	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
	t_token 	*arg = (t_token *) malloc (sizeof(t_token));

	in->str = "motest";
	in->type = (enum type) PATH;
	out->str = "example";
	out->type = (enum type) PATH;
	cmd->str = "cat";
	cmd->type = (enum type) CMD;

	command->input = &in;
	command->output = out;
	command->cmd = cmd;
	command->args = 0;

	
	return (0);
}