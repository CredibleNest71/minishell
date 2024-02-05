/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:47:26 by mresch            #+#    #+#             */
/*   Updated: 2024/02/05 15:36:52 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parse.h"
#include "../libft/libft.h"

int	double_quote(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\"')
		i++;
	if (!str[i])
		return (0);
	return (i + 1);
}

int	single_quote(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (0);
	return (i + 1);
}

int	delimiter(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 2;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	while (!is_char(str[i + j], "\n\t\v \r\f") && str[i])
		j++;
	char delimiter[j];
	j = 0;
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		delimiter[j++] = str[i++];
	delimiter[j] = 0;
	if (!ft_strnstr(&str[i], delimiter, 10000))
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == delimiter[j] && str[i])
			j++;
		if (!delimiter[j])
			return (i + j);
		i++;
	}
	return (0);
}

int	appender(char *str)
{
	int	i;

	i = 2;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	if (str[i] == '\'')
		return (i + single_quote(&str[i]));
	else if (str[i] == '\"')
		return (i + double_quote(&str[i]));
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	return (i);
}

int	redir_in(char *str)
{
	int	i;

	i = 1;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	if (str[i] == '\'')
		return (i + single_quote(&str[i]));
	else if (str[i] == '\"')
		return (i + double_quote(&str[i]));
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	return (i);
}

int	redir_out(char *str)
{
	int	i;

	i = 1;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	if (str[i] == '\'')
		return (i + single_quote(&str[i]));
	else if (str[i] == '\"')
		return (i + double_quote(&str[i]));
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	return (i);
}

int	findarg(char *str)
{
	int	i;

	i = 0;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	return (i + 1);
}

int	find_element(char *str)
{
	int	i;

	i = 0;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	if (str[i] == '\"')
		return (double_quote(&str[i]));
	else if (str[i] == '\'')
		return (single_quote(&str[i]));
	else if (!strncmp(&str[i], "<<", 2))
		return (delimiter(&str[i]));
	else if (!strncmp(&str[i], ">>", 2))
		return (appender(&str[i]));
	else if (str[i] == '<')
		return (redir_in(&str[i]));
	else if (str[i] == '>')
		return (redir_out(&str[i]));
	else
		return (findarg(&str[i]));
	return (0);
}

t_token	*make_token(char *str, int end)
{
	t_token	*token;

	token = (t_token *) ft_calloc (sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->str = ft_strndup(str, end);
	printf("\n%s", token->str);
	return (token);
}

t_token	**parse(char *str)
{
	t_token	**list;
	t_token	*temp;
	t_token	*curr;
	int		i;
	int		end;

	i = 0;
	list = (t_token **) malloc (sizeof(t_token *));
	temp = (t_token *) ft_calloc(sizeof(t_token), 1);
	end = find_element(&str[i]);
	temp = make_token(&str[i], end);
	*list = temp;
	i += end;
	while (str[i] && i < ft_strlen(str))
	{
		while (is_char(str[i], "\n\t\v \r\f") && str[i])
			i++;
		while (temp->next)
			temp = temp->next;
		end = find_element(&str[i]);
		if (end <= 0)
			return (NULL);
		temp->next = make_token(&str[i], end);
		i += end;
	}
	return (list);
}

int main(int ac, char **av)
{
	t_token **p;
	//p = parse(av[1]);
	p = parse("this is \' a test for \' me to >> know wther <\"or not the\" quotes work heyheayheay work");
	t_token *t;
	t = *p;

	int i = 1;
	while (1)
	{
		if (t->str)
			printf("\n%d	%s", i++, t->str);
		if (t->next == NULL)
			break ; 
		t = t->next;
	}
	return (0);
}

/*PSEUDO CODE:

TOKEN (STR)
{
	token **TOKENLIST 		##make tokenlist
	
	expand(STR)				##replace $$$$$$
	
	while STR				##iterate string
		find elements
		- ''		x
		- ""		x
		- <			
		- >			
		- >>		x
		- << 		x
		- | 
		strndup(element) 	##seperate token
		addtolist(list, el) ##add to tokenlist
	
	
}
*/

