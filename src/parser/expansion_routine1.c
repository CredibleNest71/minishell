/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_routine1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:48:48 by mresch            #+#    #+#             */
/*   Updated: 2024/04/29 13:36:05 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

int	expand_no_quotes(t_token **list, \
	t_token *curr, t_bigshell *data)
{
	char	*expanded;
	t_token	**addlist;

	expanded = expand(curr->str, data);
	curr->str = expanded;
	if (!expanded || !ft_strlen(expanded))
	{
		if (*list == curr)
			*list = curr->next;
		remove_token(curr);
		return (4);
	}
	if (!ft_strchr(expanded, ' '))
		return (1);
	addlist = split_to_token(expanded, curr->connected);
	(*addlist)->type = curr->type;
	insert_tokenlist(list, curr, addlist);
	free(curr->str);
	free(curr);
	free(addlist);
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

int	launch_expansion(t_token **list, \
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
		ret = expand_no_quotes(list, curr, data);
	return (ret);
}

t_token	**expander(t_token **list, t_bigshell *data)
{
	t_token	*curr;
	t_token	*next;
	int		check;

	curr = *list;
	check = 1;
	while (curr)
	{
		next = curr->next;
		if (curr->type == (e_type) HEREDOC)
			;
		else if (ft_strchr(curr->str, '$') || ft_strchr(curr->str, '~'))
			check = launch_expansion(list, curr, data);
		else
			curr->str = remove_quotes(curr->str);
		curr = next;
	}
	if (!check || !list || !*list)
		return (NULL);
	if (*list && !(*list)->str)
		return (NULL);
	join(list);
	return (list);
}