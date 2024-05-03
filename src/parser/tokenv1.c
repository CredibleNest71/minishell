/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenv1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:26 by mresch            #+#    #+#             */
/*   Updated: 2024/05/03 12:07:12 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

int	fill_token(t_token *token, char *str, int *i)
{
	int	check;

	skip_white_space(str, i);
	set_type(token, str, i);
	skip_white_space(str, i);
	if (str[*i] == '\"')
		check = quotes(token, str, i, '\"');
	else if (str[*i] == '\'')
		check = quotes(token, str, i, '\'');
	else
		check = no_quotes(token, str, i);
	if (check < 0)
		return (-1);
	if (!check)
		return (0);
	return (1);
}

t_token	*create_token(char *str, int *i)
{
	t_token	*token;
	int		check;

	token = (t_token *) ft_calloc (sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->next = NULL;
	check = fill_token(token, str, i);
	if (check <= 0)
		return (free(token), NULL);
	return (token);
}

t_token	**tokenmaker(char *str)
{
	t_token	**tokenlist;
	t_token	*new;
	int		i;

	i = 0;
	tokenlist = (t_token **) malloc (sizeof(t_token *));
	if (!tokenlist)
		return (NULL);
	*tokenlist = create_token(str, &i);
	while (1)
	{
		skip_white_space(str, &i);
		if (!str[i])
			return (tokenlist);
		new = create_token(str, &i);
		if (!new)
			return (tokenlist);
		token_list_add(tokenlist, new);
	}
	return (tokenlist);
}
