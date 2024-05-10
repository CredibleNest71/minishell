/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:59:33 by mresch            #+#    #+#             */
/*   Updated: 2024/05/06 15:34:31 by mresch           ###   ########.fr       */
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
	if (ft_strlen(token->str))
		dup->str = ft_strdup(token->str);
	else
		dup->str = (char *) ft_calloc(1, 1);
	dup->type = token->type;
	dup->quoted	= token->quoted;
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
	if (n < 0)
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
int	check_long_overflow(char *str)
{
	long long int	new;
	long long int	prev;
	int 					i;

	i = 0;
	new = 0;
	prev = 0;
	if (!str)
		return (0);
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		new = prev * 10 + (str[i] - 48);
		if (new < prev)
			return (1);
		prev = new;
		i++;
	}
	return (0);
}
