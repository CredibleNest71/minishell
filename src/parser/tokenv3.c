#include "parse.h"
#include "../minishell.h"
#include "../../libft/libft.h"

int	d_quotes(t_token *token,char *str,int *i)
{
	char	*content;
	char	*found;

	found = ft_strchr(&str[*i + 1], '\"');
	if (!found)
		return (0);
	content = ft_strndup(&str[*i], found - &str[*i]);
	if (!content)
		return (0);
	token->str = content;
	*i += found - &str[*i];
	if (str[*i + 1] && !is_char(str[*i + 1], "\n\t\v \r\f"))
		token->connected = 1;
}

int	d_quotes(t_token *token, char *str, int *i)
{
	char	*content;
	char	*found;

	found = ft_strchr(&str[*i + 1], '\'');
	if (!found)
		return (0);
	content = ft_strndup(&str[*i], found - &str[*i]);
	if (!content)
		return (0);
	token->str = content;
	*i += found - &str[*i];
	if (str[*i + 1] && !is_char(str[*i + 1], "\n\t\v \r\f"))
		token->connected = 1;
}

int	no_quotes(t_token *token, char *str, int *i)
{
	char	*content;
	int		found;

	found = 0;
	while (str[*i + found] && !is_char(str[*i + found], "\n\t\v \r\f"))
		found++;
	if (!found)
		return (0);
	content = ft_strndup(&str[*i], found);
	if (!content)
		return (0);
	token->str = content;
	*i += found;
	if (str[*i + 1] && !is_char(str[*i + 1], "\n\t\v \r\f"))
		token->connected = 1;
}

void	set_type(t_token *token, char *str, int *i)
{
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
	else
		token->type = (e_type) ARG;
	if (token->type == (e_type) HEREDOC || token->type == (e_type) APP)
		*i += 2;
	else if (token->type == (e_type) IN || token->type == (e_type) OUT)
		*i += 1;
}

int	fill_token(t_token *token,char *str,int *i)
{
	skip_white_space(&str[*i], &i);
	set_type(token, str, i);
	skip_white_space(&str[*i], &i);
	if (str[*i] == '\"')
		d_quotes(token, str, i);
	else if (str[*i] == '\'')
		s_quotes(token, str, i);
	else
		no_quotes(token, str, i);
	return (0);
}


t_token	*create_token(char *str, int *i)
{
	int		start;
	t_token	*token;

	token = (t_token *) ft_calloc (sizeof(token), 1);
	if (!token)
		return (NULL);
	fill_token(token, str, i);
}


t_token	*tokenmaker(char *str)
{
	t_token	*tokenlist;
	int		i;

	i = 0;
	while (str[i])
	{
		skip_white_space(&str[i], &i);
		if (!str[i])
			return (tokenlist);
		token_append(tokenlist, create_token(str, &i));
	}
}
