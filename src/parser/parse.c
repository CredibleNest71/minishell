/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:00:46 by mresch            #+#    #+#             */
/*   Updated: 2024/04/10 15:02:24 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include "parse.h"

// void	print_cmds(t_command *cmd, t_bigshell *data)
// {
// 	if (!cmd)
// 	{
// 		write(2, "(NO COMMANDS)\n", 15);
// 		return ;
// 	}
// 	t_command *temp_cmd = cmd;
// 	printf("\n==========================================\n");
// 	printf("==========================================\n");
// 	printf("==	NUMBER OF COMMANDS: %d\n", data->num_cmd);
// 	printf("==========================================\n");
// 	if (data->heredoc)
// 	{
// 		for (t_token *temp = (data->heredoc); temp; temp = temp->next)
// 			printf("==	HEREDOCS:		%s\n", temp->str);
// 	}
// 	else
// 		printf("=	NO HEREDOCS\n");
// 	printf("==========================================\n");
// 	for (;temp_cmd; temp_cmd = temp_cmd->next)
// 	{
// 		printf("==========================================\n");
// 		if (temp_cmd->cmd)
// 			printf("== COMMAND(%d):%s\n",temp_cmd->arg_num, temp_cmd->cmd->str);
// 		printf("== ");
// 		for (int i = 0; i < temp_cmd->arg_num + 1; i++)
// 		{
// 			printf("[%s]", temp_cmd->args_exec[i]);
// 		}
// 		printf("\n");
// 		for (t_token *curr = temp_cmd->args;curr; curr = curr->next)
// 			printf("==	ARG:		%s\n", curr->str);
// 		for (t_token *curr = temp_cmd->input;curr; curr = curr->next)
// 		{
// 			if (curr->type == (e_type) IN)
// 				printf("==	IN:			%s\n", curr->str);
// 			else if (curr->type == (e_type) HEREDOC)
// 				printf("==	HEREDOC: 	%s\n", curr->str);
// 		}
// 		for (t_token *curr = temp_cmd->output; curr; curr = curr->next)
// 		{
// 			if (curr->type == (e_type) APP)
// 				printf("==	APP:			%s\n", curr->str);
// 			else
// 				printf("==	OUT:			%s\n", curr->str);
// 		}
// 	}
// 	printf("==========================================\n\n");
// }

static int	set_counts(t_command *cmd, t_bigshell *data)
{
	t_command	*temp;
	t_token		*arg;
	int			i;
	int			j;

	j = 0;
	temp = cmd;
	while (temp)
	{
		if (temp->cmd)
			j++;
		i = 0;
		arg = temp->args;
		while (arg)
		{
			i++;
			arg = arg->next;
		}
		temp->arg_num = i;
		temp = temp->next;
	}
	if (data)
		data->num_cmd = j;
	return (j);
}

void	set_char_array(t_command *final)
{
	t_token		*temparg;
	int			i;

	final->args_exec = (char **) ft_calloc (sizeof(char *), final->arg_num + 3);
	if (!final->args_exec)
		return ;
	i = 0;
	if (final && final->cmd)
		final->args_exec[i++] = ft_strdup(final->cmd->str);
	temparg = final->args;
	while (temparg)
	{
		final->args_exec[i] = ft_strdup(temparg->str);
		temparg = temparg->next;
		i++;
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

void	heredocs_to_bigshell(t_token **tokens, t_bigshell *data)
{
	t_token	*temp;
	t_token	*new;

	if (!tokens || !data || !(*tokens))
		return ;
	temp = *tokens;
	while (temp)
	{
		if (temp->type == (e_type) HEREDOC)
		{
			new = token_dup(temp);
			if (!data->heredoc)
				data->heredoc = new;
			else
				ft_tokenlast(data->heredoc)->next = new;
		}
		temp = temp->next;
	}
}

t_command	*parse(char *input, t_bigshell *data)
{
	t_token		**tokens;
	t_command	**cmds;
	t_command	*ret;

	if (!input)
		return (NULL);
	if (!check_syntax(data, input))
		return (NULL);
	tokens = tokenmaker(input);
	tokens = expander(tokens, data);
	if (!tokens | !(*tokens))
		return (NULL);
	heredocs_to_bigshell(tokens, data);
	cmds = commands_finalized(tokens);
	set_counts(*cmds, data);
	set_all_char_arrays(*cmds);
	delete_token_list(*tokens);
	free(tokens);
	ret = *cmds;
	free(cmds);
	return (ret);
}
