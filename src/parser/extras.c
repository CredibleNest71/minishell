/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:59:33 by mresch            #+#    #+#             */
/*   Updated: 2024/04/24 14:06:27 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"

void	token_append(t_token *lst, t_token *token)
{
	if (!token)
		return ;
	if (!lst)
	{
		lst = token;
		return ;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = token;
}

//duplicates, next->NULL
t_token	*token_dup(t_token *token)
{
	t_token	*dup;

	dup = (t_token *) ft_calloc (sizeof(t_token), 1);
	if (!dup)
		return (NULL);
	dup->str = ft_strdup(token->str);
	dup->type = token->type;
	dup->next = NULL;
	dup->prev = NULL;
	return (dup);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*ans;

	i = 0;
	if (n <= 0)
		return (NULL);
	ans = malloc(n + 1);
	if (!ans)
		return (0);
	while (s[i] && i < n)
	{
		ans[i] = s[i];
		i++;
	}
	ans[i] = 0;
	return (ans);
}
