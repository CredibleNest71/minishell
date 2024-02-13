/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:47:26 by mresch            #+#    #+#             */
/*   Updated: 2024/02/09 15:28:05 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parse.h"
#include "../libft/libft.h"

int	double_quote(char *str)
{
	int	i;

	i = 1;
	printf("ENTER in doublequote()");
	if (!str)
		return (0);
	while (str[i] && str[i] != '\"')
		i++;
	printf("segfault not in doublequote()");
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

int	redir(char *str)
{
	int	i;
	int	quotes;

	i = 1;
	quotes = -1;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	if (str[i] == '\'')
		quotes = single_quote(&str[i]);
	else if (str[i] == '\"')
		quotes = double_quote(&str[i]);
	if (quotes == 0)
		return (0);
	else if (quotes > 0)
		return (i + quotes);
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	return (i);
}

// int	redir_out(char *str)
// {
// 	int	i;
// 	int	quotes;

// 	quotes = -1;
// 	i = 1;
// 	while (is_char(str[i], "\n\t\v \r\f") && str[i])
// 		i++;
// 	if (str[i] == '\'')
// 		quotes = single_quote(&str[i]);
// 	else if (str[i] == '\"')
// 		quotes = double_quote(&str[i]);
// 	if (!quotes)
// 		return (0);
// 	else if (quotes > 0);
// 		return (i + quotes);
// 	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
// 		i++;
// 	return (i);
// }

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
	if (!str)
		return (0);
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
		return (redir(&str[i]));
	else if (str[i] == '>')
		return (redir(&str[i]));
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
	if (!str || end <= 0)
		return (0);
	token->str = ft_strndup(str, end);
	//printf("\n%s", token->str);
	return (token);
}

void	delete_token_list(t_token **list)
{
	t_token	*temp;
	t_token *next;

	temp = *list;
	while (temp)
	{
		free(temp->str);
		next = temp->next;
		free(temp);
		temp = next;
	}
	free(list);
}

t_token	**parse(char *str)
{
	t_token	**list;
	t_token	*temp;
	int		i;
	int		end;

	if (!str)
		return (NULL);
	i = 0;
	end = 0;
	list = (t_token **) malloc (sizeof(t_token *));
	if (!list)
		return (NULL);
	temp = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!temp)
		return (NULL);
	end = find_element(str);
	temp = make_token(str, end);
	*list = temp;
	i += end;
	while ( i < ft_strlen(str) && str[i])
	{
		while (is_char(str[i], "\n\t\v \r\f") && str[i])
			i++;
		while (temp->next)
			temp = temp->next;
		end = find_element(&str[i]);
		if (end <= 0)
			return (delete_token_list(list), NULL);
		temp->next = make_token(&str[i], end);
		i += end;
	}
	return (list);
}

int main(int ac, char **av)
{
	t_token **p;
	char *test;
	test = ft_strdup("this is  a test for \' me to >> know | wther <  adjsadfjfsd   not hea asd the quotes work heyheayheay work");
	if (ac == 2)
		p = parse(av[1]);
	else 
		p = parse(test);
	if (!p)
		return (28);
	t_token *t;
	t = *p;

	int i = 1;
	//classify(t);
	//mark_commands(t);
	char *names[] = {"CMD", "ARG", "PIPE", "IN", "OUT", "APP", "HERE"};
	while (1)
	{
		if (t->str)
		{
			//clean_token(t);
			printf("\n%d: %s	%s", i++, names[t->type], t->str);
		}
		if (t->next == NULL)
			break ;
		t = t->next;
	}
	t_command *cmd = transform(*p);
	if (!cmd)
		printf("command creation failed \n");
	for (;cmd; cmd = cmd->next)
	{
		printf("\n=====================");
		printf("\nCOMMNAND:		%s", cmd->cmd->str);
		for (t_token *curr = cmd->args;curr; curr = curr->next)
			printf("\n	ARG:		%s", curr->str);
		if (cmd->input)
			printf("\nIN:			%s", cmd->input->str);
		if (cmd->output)
			printf("\nOUT:			%s", cmd->output->str);
		if (cmd->append)
			printf("\nAPP:			%s", cmd->append->str);
		if (cmd->heredoc)
			printf("\nHERE:			%s", cmd->heredoc->str);
		printf("\n=====================");
	}
	free(test);
	delete_token_list(p);
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
