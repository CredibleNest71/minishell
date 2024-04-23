/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenextras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:47:26 by mresch            #+#    #+#             */
/*   Updated: 2024/04/23 13:23:01 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"

void	delete_token(t_token *token)
{
	if (!token)
		return ;
	if (token->str)
		free(token->str);
	free(token);
	return ;
}

void	delete_token_list(t_token *list)
{
	t_token	*temp;
	t_token	*next;

	temp = list;
	if (!list)
		return ;
	while (temp)
	{
		next = temp->next;
		delete_token(temp);
		temp = next;
	}
}

void	delete_char_array(char **arr)
{
	int	i;
	int	count;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		i++;
	count = i;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	delete_command_list(t_command *cmd)
{
	t_command	*prev;

	while (cmd)
	{
		delete_token_list(cmd->input);
		delete_token_list(cmd->output);
		delete_token_list(cmd->cmd);
		delete_token_list(cmd->args);
		delete_char_array(cmd->args_exec);
		prev = cmd;
		cmd = cmd->next;
		free(prev);
	}
}

void	token_list_add(t_token **tokenlist, t_token *token)
{
	t_token	*temp;

	if (!tokenlist || !token)
		return ;
	if (!(*tokenlist))
	{
		*tokenlist = token;
		return ;
	}
	temp = *tokenlist;
	while (temp->next)
		temp = temp->next;
	temp->next = token;
	token->prev = temp;
	return ;
}