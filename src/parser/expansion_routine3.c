/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_routine3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:29:19 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 13:37:17 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../minishell.h"

t_token	*make_t(char *str)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->str = str;
	token->type = (t_type) ARG;
	return (token);
}

t_token	**split_to_token(char *expanded, int join)
{
	t_token	**ret;
	t_token	*new;
	char	**split;
	int		i;

	i = 0;
	if (!expanded || !ft_strlen(expanded))
		return (NULL);
	split = ft_split(expanded, ' ');
	if (!split || !*split)
		return (free(split), NULL);
	ret = (t_token **) ft_calloc (sizeof(t_token *), 1);
	while (split[i])
	{
		new = make_t(split[i]);
		token_list_add(ret, new);
		i++;
	}
	free(split);
	if (is_char(expanded[0], SPACE3))
		(*ret)->distanced = 1;
	if (join && !is_char(expanded[ft_strlen(expanded) - 1], SPACE3))
		new->connected = 1;
	return (ret);
}

void	insert_tokenlist(t_token **list, \
		t_token *curr, t_token **addlist)
{
	t_token	*next;
	t_token	*last;

	if (!addlist)
		return ;
	next = curr->next;
	if (curr->prev)
	{
		curr->prev->next = *addlist;
		(*addlist)->prev = curr->prev;
	}
	else
		*list = *addlist;
	last = ft_tokenlast(*addlist);
	last->next = next;
	if (next)
		next->prev = last;
	free(addlist);
	free(curr->str);
	free(curr);
}

void	remove_token(t_token *curr)
{
	t_token	*prev;
	t_token	*next;

	if (!curr)
		return ;
	prev = curr->prev;
	next = curr->next;
	if (prev && next)
	{
		prev->next = next;
		next->prev = prev;
	}
	else if (prev)
		prev->next = NULL;
	else if (next)
		next->prev = NULL;
	if (curr->str)
		free(curr->str);
	curr->str = NULL;
	free(curr);
}
