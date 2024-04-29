/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:24:51 by mresch            #+#    #+#             */
/*   Updated: 2024/04/23 13:25:01 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"

int	is_char(char c, char *chars)
{
	int		i;

	i = -1;
	while (chars[++i])
		if (chars[i] == c)
			return (1);
	return (0);
}

void	skip_chars(char *str, int *i)
{
	while (!is_char(str[*i], "\n\t\v \r\f") && str[*i])
		*i += 1;
}

void	skip_white_space(char *str, int *i)
{
	if (!str)
		return ;
	while (str[*i] && is_char(str[*i], "\n\t\v \r\f"))
		*i += 1;
}

int	ft_token_count(t_token **list)
{
	int		i;
	t_token	*temp;

	if (!list || !*list)
		return (0);
	temp = *list;
	i = 0;
	while (temp)
	{
		i++;
		printf("counter: %d:	'%s'\n", i, temp->str);
		temp = temp->next;
	}
	return (i);
}
