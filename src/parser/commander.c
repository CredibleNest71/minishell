#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

void	mark_cmds(t_token **list)
{
	t_token	*temp;
	int		pipe;

	temp = *list;
	pipe = 1;
	while (temp)
	{
		if (temp->type == (e_type) ARG && pipe)
		{
			temp->type = (e_type) CMD;
			pipe = 0;
		}
		else if (temp->type == (e_type) PIPE)
			pipe = 1;
		temp = temp->next;
	}
}

void	assign(t_command *cmd, t_token *token)
{
	if (token->type == (e_type) CMD)
		cmd->cmd = token_dup(token);
	if (token->type == (e_type) ARG)
		token_list_add(&cmd->args, token_dup(token));
	if (token->type == (e_type) IN)
		token_list_add(&cmd->input, token_dup(token));
	if (token->type == (e_type) OUT)
		token_list_add(&cmd->output, token_dup(token));
}

void	add_to_command_list(t_command **list, t_command *cmd)
{
	t_command	*temp;

	if (!list || !cmd)
		return ;
	if (!*list)
	{
		*list = cmd;
		return ; 
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = cmd;
}

t_command	**create_commandlist(t_token **list)
{
	int			pipe;
	t_command	**final;
	t_command	*cmd;
	t_token		*temp;

	pipe = 1;
	temp = *list;
	final = (t_command **) ft_calloc (sizeof(t_command *), 1);
	cmd = (t_command *) ft_calloc (sizeof(t_command), 1);
	if (!final || !cmd)
		return (NULL);
	while (temp)
	{
		if (pipe)
		{
			cmd = (t_command *) ft_calloc (sizeof(t_command), 1);
			add_to_command_list(final, cmd);
			pipe = 0;
		}
		assign(cmd, temp);
		if (temp->type == (e_type) PIPE)
			pipe = 1;
		temp = temp->next;
	}
	return (final);
}

t_command   **commands_finalized(t_token **list)
{
	t_command	**final;

	mark_cmds(list);
	final = create_commandlist(list);
	return (final);
}