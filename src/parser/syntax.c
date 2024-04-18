/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:54:17 by mresch            #+#    #+#             */
/*   Updated: 2024/04/16 12:35:49 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

int	skip_quotes(char *str, int *i, char c)
{
	char	*here;

	here = ft_strchr(&str[*i + 1], c);
	if (!here)
		return (0);
	else
		*i = here - str + 1;
	return (1);
}

int	check_arrows(char *str, int *i, char c)
{
	int	amount;

	amount = 0;
	while (str[*i] == c)
	{
		amount++;
		*i += 1;
	}
	if (amount > 2)
		return (0);
	while (is_char(str[*i], SPACE3))
		*i += 1;
	if (!str[*i] || is_char(str[*i], "<>|"))
		return (0);
	return (1);
}

int	check_specials(char *str, int *i)
{
	char	c;

	c = str[*i];
	if (c == '\'' || c == '\"')
		return (skip_quotes(str, i, c));
	else if (c == '|')
	{
		*i += 1;
		while (is_char(str[*i], SPACE3))
			*i += 1;
		if (str[*i] == '|')
			return (0);
	}
	else if (c == '<' || c == '>')
		return (check_arrows(str, i, c));
	return (1);
}

int	check_end_on_pipe(char *s)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(s) - 1;
	while (len + 1)
	{
		if (is_char(s[len], "<>|"))
			return (1);
		if (is_char(s[len], SPACE3))
			len--;
		else
			break ;
	}
	while (s[i] && is_char(s[i], SPACE3))
		i++;
	if (is_char(s[i], "<>|"))
		return (1);
	return (0);
}

int	check_syntax(t_bigshell *data, char *str)
{
	int		i;
	int		check;

	i = 0;
	check = 1;
	if (check_end_on_pipe(str))
		check = 0;
	while (str[i] && check)
	{
		if (is_char(str[i], "\'\"|<>"))
			check = check_specials(str, &i);
		else
			i++;
	}
	if (!check)
	{
		write(2, "SYNTAX ERROR\n", 14);
		update_exit_stat(data, 2);
	}
	return (check);
}
