/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_routine2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:27:10 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 13:37:16 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../minishell.h"

void	mark_join(t_token **list)
{
	t_token	*curr;

	curr = *list;
	while (curr)
	{
		if (curr->prev)
		{
			if (curr->distanced)
				curr->prev->connected = 0;
		}
		curr = curr->next;
	}
}

static int	do_join(t_token *curr, char *jstr)
{
	t_token	*next;

	next = curr->next;
	if (curr->type == (t_type) PIPE)
		;
	else if (curr->connected && next && next->type == (t_type) ARG)
	{
		if (!ft_strncmp(curr->str, "$", 2))
		{
			free(curr->str);
			curr->str = NULL;
		}
		jstr = ft_strjoin(curr->str, next->str);
		free(curr->str);
		free(next->str);
		curr->str = jstr;
		curr->connected = next->connected;
		curr->next = next->next;
		if (next->quoted)
			curr->quoted = 1;
		free(next);
		return (1);
	}
	return (0);
}

void	join(t_token **list)
{
	t_token	*curr;
	char	*jstr;

	if (!list || !*list)
		return ;
	curr = *list;
	mark_join(list);
	jstr = NULL;
	while (curr)
	{
		if (do_join(curr, jstr))
			continue ;
		curr = curr->next;
	}
}

int	tilde(t_token *curr, t_bigshell *data)
{
	char	*home;
	char	*joined;

	if (curr->str[0] != '~')
		return (0);
	home = ft_strdup(get_val("HOME", data));
	if (!home)
		return (write(2, "error getting value\n", 21));
	if (!ft_strncmp(curr->str, "~", 2))
	{
		free(curr->str);
		curr->str = home;
	}
	else if (!ft_strncmp(curr->str, "~/", 2))
	{
		joined = ft_strjoin(home, curr->str + 1);
		free(curr->str);
		free(home);
		curr->str = joined;
	}
	else
		free(home);
	return (0);
}
