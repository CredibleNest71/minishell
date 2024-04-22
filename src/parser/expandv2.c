/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandv2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:48:48 by mresch            #+#    #+#             */
/*   Updated: 2024/04/22 16:48:14 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

t_token	*make_t(char *str)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->str = str;
	token->type = (e_type) ARG;
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
	ret = (t_token **) ft_calloc (sizeof(t_token *), 1);
	while (split[i])
	{
		new = make_t(split[i]);
		token_list_add(ret, new);
		i++;
	}
	if (is_char(expanded[0], SPACE3))
		(*ret)->distanced = 1;
	if (join && !is_char(expanded[ft_strlen(expanded) - 1], SPACE3))
		new->connected = 1;
	return (ret);
}

void	insert_tokenlist(t_token **list, t_token *prev, \
		t_token *curr, t_token **addlist)
{
	t_token	*next;
	t_token	*last;

	if (!addlist)
		return ;
	next = curr->next;
	if (prev)
	{
		prev->next = *addlist;
		(*addlist)->prev = prev;
	}
	else
		*list = *addlist;
	last = ft_tokenlast(*addlist);
	last->next = next;
	if (next)
		next->prev = last;
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
	free(curr->str);
	curr->str = NULL;
	free(curr);
}

int	expand_no_quotes(t_token **list, t_token *prev, \
	t_token *curr, t_bigshell *data)
{
	char	*expanded;
	t_token	**addlist;

	expanded = expand(curr->str, data);
	if (!expanded || !ft_strlen(expanded))
	{
		if (*list == curr)
			*list = curr->next;
		remove_token(curr);
		return (4);
	}
	addlist = split_to_token(expanded, curr->connected);
	if (curr->type >= 3 && curr->type <= 6 && ft_token_count(addlist) > 1)
	{
		write(2, "AMBIGUOUS REDIRECT\n", 20);
		return (0);
	}
	(*addlist)->type = curr->type;
	insert_tokenlist(list, prev, curr, addlist);
	return (1);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	if (!is_char(str[0], "\"\'"))
		return (str);
	len = ft_strlen(str);
	ret = ft_strndup(&str[1], len - 2);
	free(str);
	return (ret);
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
		joined = ft_strjoin(home, curr->str);
		free(curr->str);
		free(home);
		curr->str = joined;
	}
	return (0);
}

int	launch_expansion(t_token **list, t_token *prev, \
	t_token *curr, t_bigshell *data)
{
	int	ret;

	ret = 1;
	if (strchr(curr->str, '~'))
		tilde(curr, data);
	if (!strchr(curr->str, '$'))
		return (1);
	if (curr->str[0] == '\'')
	{
		curr->str = remove_quotes(curr->str);
	}
	else if (curr->str[0] == '\"')
	{
		curr->str = remove_quotes(curr->str);
		curr->str = expand(curr->str, data);
	}
	else
		ret = expand_no_quotes(list, prev, curr, data);
	return (ret);
}

static	void	mark_join(t_token **list)
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

void	join(t_token **list)
{
	t_token	*curr;
	t_token	*next;
	char	*jstr;

	if (!list || !*list)
		return ;
	curr = *list;
	mark_join(list);
	while (curr)
	{
		next = curr->next;
		if (curr->type == (e_type) PIPE)
			;
		else if (curr->connected && next && next->type == (e_type) ARG)
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
			free(next);
			continue ;
		}
		curr = curr->next;
	}
}

t_token	**expander(t_token **list, t_bigshell *data)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*next;
	int		check;

	curr = *list;
	prev = NULL;
	check = 1;
	while (curr)
	{
		next = curr->next;
		if (curr->type == (e_type) HEREDOC)
			;
		else if (ft_strchr(curr->str, '$') || ft_strchr(curr->str, '~'))
			check = launch_expansion(list, prev, curr, data);
		else
			curr->str = remove_quotes(curr->str);
		if (check != 4)
			prev = curr;
		curr = next;
	}
	if (!check || !list || !*list)
		return (NULL);
	if (*list && !(*list)->str)
		return (NULL);
	join(list);
	return (list);
}
