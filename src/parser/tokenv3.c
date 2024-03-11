/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:47:26 by mresch            #+#    #+#             */
/*   Updated: 2024/03/07 12:20:40 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"

char	*cfindarg(char *str);

char	*double_quote(char *str)
{
	int	i;
    char *ret;
    char *temp;

	i = 1;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\"')
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '\"')
		i++;
    ret = ft_strndup(str, i);
	if (str[i] && !is_char(str[i], "\n\t\v \r\f"))
	{
        temp = ret;
        ret = ft_strjoin(ret, cfindarg(&str[i]));
        free(temp);
	}
    temp = ret;
    expand(ret);
    free(temp);
	return (ret);
}

char *single_quote(char *str)
{
	int	i;
    char *ret;
    char *temp;

	i = 1;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '\'')
		i++;
    ret = ft_strndup(str, i);
	if (str[i] && !is_char(str[i], "\n\t\v \r\f"))
	{
        temp = ret;
        ret = ft_strjoin(ret, cfindarg(&str[i]));
        free(temp);
	}
	return (ret);
}

// int	delimiter(char *str)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 2;
// 	while (is_char(str[i], "\n\t\v \r\f") && str[i])
// 		i++;
// 	while (!is_char(str[i + j], "\n\t\v \r\f") && str[i])
// 		j++;
// 	char delimiter[j];
// 	j = 0;
// 	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
// 		delimiter[j++] = str[i++];
// 	delimiter[j] = 0;
// 	if (!ft_strnstr(&str[i], delimiter, 10000))
// 		return (0);
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[i + j] == delimiter[j] && str[i])
// 			j++;
// 		if (!delimiter[j])
// 			return (i + j);
// 		i++;
// 	}
// 	return (0);
// }

// int	appender(char *str)
// {
// 	int	i;

// 	i = 2;
// 	while (is_char(str[i], "\n\t\v \r\f") && str[i])
// 		i++;
// 	if (str[i] == '\'')
// 		return (i + single_quote(&str[i]));
// 	else if (str[i] == '\"')
// 		return (i + double_quote(&str[i]));
// 	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
// 		i++;
// 	return (i);
// }

static char	*find_redir(char *str)
{
	int	i;
	int	quotes;
    char *ret; 
    char *temp;

	i = 1;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
    ret = ft_strndup(str, i);
	if (str[i] == '\'')
		ret = ft_strjoin(ret, single_quote(&str[i]));
	else if (str[i] == '\"')
		ret = ft_strjoin(ret, double_quote(&str[i]));
	else
        ret = cfindarg(&str[i]);
	return (ret);
}

char *delimiter(char *str)
{
	return (find_redir(&str[1]) + 1);
}

char *cfindarg(char *str)
{
	int	i;
    char *ret;
    char *temp;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && is_char(str[i], "\n\t\v \r\f"))
		i++;
	while (str[i] && !is_char(str[i], "\n\t\v \r\f|\"\'"))
	{
        if (is_char(str[i + 1], "|"))
            return (ft_strndup(str, i + 1));
		i++;
	}
    ret = ft_strndup(str, i);
	if (str[i] == '\"')
	{
        temp = ret;
        ret = ft_strjoin(ret, double_quote(&str[i]));
        free(temp);
    }
	else if (str[i] == '\'')
	{
        temp = ret;
        ret = ft_strjoin(ret, single_quote(&str[i]));
        free(temp);
    }
	return (ret);
}

char	*find_element(char *str)
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
		//find_redir(&str[i + 1]);
	// else if (!strncmp(&str[i], ">>", 2))
	// 	return (appender(&str[i]));
	else if (str[i] == '<')
		return (find_redir(&str[i]));
	else if (str[i] == '>')
		return (find_redir(&str[i]));
	else
		return (cfindarg(&str[i]));
	return (0);
}

t_token	*make_token(char *str)
{
	t_token	*token;
	token = (t_token *) ft_calloc (sizeof(t_token), 1);
	if (!token)
		return (NULL);
	if (!str)
		return (0);
	token->str = ft_strdup(str);
	return (token);
}

void	delete_token_list(t_token *list)
{
	t_token	*temp;
	t_token *next;

	temp = list;
	while (temp)
	{
		//printf("\nfreeing: %s", temp->str);
		free(temp->str);
		if (temp->delimiter)
			free(temp->delimiter);
		next = temp->next;
		free(temp);
		temp = next;
	}
}

void	delete_command_list(t_command *cmd)
{
	t_command	*prev;

	while (cmd)
	{
		delete_token_list(cmd->input);
		delete_token_list(cmd->output);
		delete_token_list(cmd->cmd);
		delete_token_list(cmd->args);
		prev = cmd;
		cmd = cmd->next;
		free(prev);
	}
}

t_token	*parse_tokens(char *str)
{
	t_token	*list;
	t_token	*temp;
	int		i;
	int		end;
    char    *content;

	if (!str)
		return (NULL);
	i = 0;
	content = find_element(str);
	temp = make_token(content);
    i += ft_strlen(content);
	list = temp;
	skip_white_space(str, &i);
	while (/* i < (int) ft_strlen(str) && */ str[i])
	{
		temp = ft_tokenlast(temp);
		content = find_element(&str[i]);
		if (!content)
			return (delete_token_list(list), NULL);
		temp->next = make_token(content);
        i += ft_strlen(content);
		skip_white_space(str, &i);
	}
	return (list);
}


// int main(int ac, char **av)
// {
// 	t_token *p;
// 	char *test;
// 	//test = ft_strdup("this is  a test for \' me to >> know | wther <  adjsadfjfsd   not hea asd the quotes work heyheayheay work");
// 	if (ac == 2)
// 		p = parse(av[1]);
// 	else 
// 		p = parse(test);
// 	if (!p)
// 		return (28);
// 	t_token *t;
// 	t = p;

// 	int i = 1;
// 	//classify(t);
// 	//mark_commands(t);
// 	char *names[] = {"CMD", "ARG", "PIPE", "IN", "OUT", "APP", "HERE"};
// 	while (1)
// 	{
// 		if (t->str)
// 		{
// 			//clean_token(t);
// 			printf("\n%d: %s	%s", i++, names[t->type], t->str);
// 		}
// 		if (t->next == NULL)
// 			break ;
// 		t = t->next;
// 	}
// 	t_command *cmd = transform(p);
// 	if (!cmd)
// 		printf("command creation failed \n");
// 	t_command *temp_cmd = cmd;
// 	for (;temp_cmd; temp_cmd = temp_cmd->next)
// 	{
// 		printf("\n==========================================");
// 		printf("\nCOMMAND:		%s", temp_cmd->cmd->str);
// 		for (t_token *curr = temp_cmd->args;curr; curr = curr->next)
// 			printf("\n	ARG:		%s", curr->str);
// 		for (t_token *curr = temp_cmd->input;curr; curr = curr->next)
// 			printf("\nIN:			%s", curr->str);
// 		for (t_token *curr = temp_cmd->output;curr; curr = curr->next)
// 			printf("\nOUT:			%s", curr->str);
// 		for (t_token *curr = temp_cmd->append;curr; curr = curr->next)
// 			printf("\nAPP:			%s", curr->str);
// 		for (t_token *curr = temp_cmd->heredoc;curr; curr = curr->next)
// 			printf("\nHere:			%s", curr->str);
// 		printf("\n==========================================");
// 	}
// 	//free(test);
// 	delete_command_list(cmd);
// 	return (0);
// }

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
