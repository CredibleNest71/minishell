/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:00:46 by mresch            #+#    #+#             */
/*   Updated: 2024/05/08 14:11:44 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include "parse.h"

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
	if (final && final->cmd && ft_strlen(final->cmd->str))
		final->args_exec[i++] = ft_strdup(final->cmd->str);
	else
		final->args_exec[i++] = ft_calloc(1, 1);
	temparg = final->args;
	while (temparg)
	{
		if (ft_strlen(temparg->str))
			final->args_exec[i] = ft_strdup(temparg->str);
		else
			final->args_exec[i] = ft_calloc(1, 1);
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
	if (!tokens)
		return (NULL);
	if (!*tokens)
		return (free(tokens), NULL);
	heredocs_to_bigshell(tokens, data);
	cmds = commands_finalized(tokens, data);
	if (!cmds)
		return (NULL);
	set_counts(*cmds, data);
	set_all_char_arrays(*cmds);
	delete_token_list(*tokens);
	free(tokens);
	ret = *cmds;
	free(cmds);
	return (ret);
}
