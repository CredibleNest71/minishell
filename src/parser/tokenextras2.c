/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenextras2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:41:37 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 12:21:01 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"

int	quotes(t_token *token, char *str, int *i, char quote)
{
	char	*content;
	char	*found;

	found = ft_strchr(&str[*i + 1], quote);
	if (!found)
		return (-1);
	content = ft_strndup(&str[*i], found - &str[*i] + 1);
	if (!content)
		return (0);
	token->str = content;
	*i += found - &str[*i] + 1;
	if (str[*i] && !is_char(str[*i], "\n\t\v \r\f"))
		token->connected = 1;
	token->quoted = 1;
	return (1);
}

int	no_quotes(t_token *token, char *str, int *i)
{
	char	*content;
	int		found;

	found = 0;
	if (is_char(str[*i], "|"))
		found = 1;
	else
	{
		if (is_char(str[*i], "$"))
			found++;
		while (str[*i + found] && \
		!is_char(str[*i + found], "<>$|\"\'\n\t\v \r\f"))
			found++;
	}
	if (!found)
		return (0);
	content = ft_strndup(&str[*i], found);
	if (!content)
		return (0);
	token->str = content;
	*i += found;
	if (str[*i] && !is_char(str[*i], "\n\t\v \r\f"))
		token->connected = 1;
	return (1);
}

void	set_type(t_token *token, char *str, int *i)
{
	if (!token)
		return ;
	if (is_char(str[*i], "\"\'"))
		token->type = (t_type) ARG;
	else if (!strncmp(&str[*i], "<<", 2))
		token->type = (t_type) HEREDOC;
	else if (!strncmp(&str[*i], ">>", 2))
		token->type = (t_type) APP;
	else if (str[*i] == '<')
		token->type = (t_type) IN;
	else if (str[*i] == '>')
		token->type = (t_type) OUT;
	else if (str[*i] == '|')
		token->type = (t_type) PIPE;
	else
		token->type = (t_type) ARG;
	if (token->type == (t_type) HEREDOC || token->type == (t_type) APP)
		*i += 2;
	else if (token->type == (t_type) IN || token->type == (t_type) OUT)
		*i += 1;
}
