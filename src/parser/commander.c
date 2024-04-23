/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:44:18 by mresch            #+#    #+#             */
/*   Updated: 2024/04/23 17:07:00 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (token->type == (e_type) APP)
		token_list_add(&cmd->output, token_dup(token));
	if (token->type == (e_type) HEREDOC)
		token_list_add(&cmd->input, token_dup(token));
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
	cmd->prev = temp;
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
	if (!final)
		return (NULL);
	while (temp)
	{
		if (pipe)
		{
			cmd = (t_command *) ft_calloc (sizeof(t_command), 1);
			add_to_command_list(final, cmd);
			pipe = 0;
		}
		if (temp->type == (e_type) PIPE)
			pipe = 1;
		assign(cmd, temp);
		temp = temp->next;
	}
	return (final);
}

t_command	**commands_finalized(t_token **list)
{
	t_command	**final;

	mark_cmds(list);
	final = create_commandlist(list);
	return (final);
}
