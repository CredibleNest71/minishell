#include "parse.h"
#include "../../minishell.h"
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
	return (1);
}

int	no_quotes(t_token *token, char *str, int *i)
{
	char	*content;
	int		found;

	found = 0;
	if (is_char(str[*i], "|"))
		found++;
	else
	{
		if (is_char(str[*i], "$"))
			found++;
		while (str[*i + found] && !is_char(str[*i + found], "$|\"\'\n\t\v \r\f"))
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
		token->type = (e_type) ARG;
	else if (!strncmp(&str[*i], "<<", 2))
		token->type = (e_type) HEREDOC;
	else if (!strncmp(&str[*i], ">>", 2))
		token->type = (e_type) APP;
	else if (str[*i] == '<')
		token->type = (e_type) IN;
	else if (str[*i] == '>')
		token->type = (e_type) OUT;
	else if (str[*i] == '|')
		token->type = (e_type) PIPE;
	else
		token->type = (e_type) ARG;
	if (token->type == (e_type) HEREDOC || token->type == (e_type) APP)
		*i += 2;
	else if (token->type == (e_type) IN || token->type == (e_type) OUT)
		*i += 1;
}

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
	//printf("tokencontent: %s\n", token->str);
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

void	token_list_add(t_token **tokenlist, t_token *token)
{
	t_token	*temp;

	if (!tokenlist || !token)
		return ;
	if (!(*tokenlist))
	{
		*tokenlist = token;
		return ;
	}
	temp = *tokenlist;
	while (temp->next)
		temp = temp->next;
	temp->next = token;
	token->prev = temp;
	return ;	
}

t_token	**tokenmaker(char *str)
{
	t_token	**tokenlist;
	t_token	*new;
	int		i;

	i = 0;
	tokenlist = (t_token **) malloc (sizeof(t_token **));
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

/*
int	main(int ac, char **av)
{
	t_token	**tokens;
	t_token	*curr;
	t_bigshell	data;

	tokens = tokenmaker(av[1]);
	tokens = expander(tokens, NULL);
	
	if (tokens)
		curr = *tokens;
	else
		return (printf("ERROR"));
	while (curr &&curr->str)
	{
		printf("%s\n", curr->str);
		printf("type %d\n", curr->type);
		printf("connected: %d\n\n", curr->connected);
		curr = curr->next;
	}
}
*/