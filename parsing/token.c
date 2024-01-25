#include "../minishell.h"
#include "parse.h"

int	is_redir(char *str)
{
	int	i;
	char	*seperators[] = {"<", ">", ">>", "<<", NULL};
	
	i = 0;
	if (!str)
		return (0);
	while (seperators[i])
	{
		if (!ft_strncmp(str, seperators[i++], 3))
			return (1);
	}
	return (0);
}

int	is_nexus(char *str)
{
	int	i;
	char	*seperators[] = {"|", "||", "&", "&&", NULL};
	
	i = 0;
	if (!str)
		return (0);
	while (seperators[i])
	{
		if (!ft_strncmp(str, seperators[i++], 3))
			return (1);
	}
	return (0);
}

t_token	*tokenify(char *str)
{
	t_token *token;

	token = (t_token *) malloc(sizeof(t_token));
	token->str = str;
    if (is_nexus(str))
        token->type = (e_type) NEX;    
    else if (is_redir(str))
        token->type = (e_type) DIR;
    else
        token->type = (e_type) ARG;
	return (token);
}
////////////////////////////////////////////////////////////////////////////

int	is_whitespace(char c)
{
	int		i;
	char	spaces[] = {'\f', '\n', ' ', '\r', '\t', '\v', 0};

	i = -1;
	while (spaces[++i])
		if (spaces[i] == c)
			return (1);
	return (0);
}

//returns 0 for legit quotes
int	check_quotes(char *str)
{
	int	count_doubles;
	int	count_singles;
	int	i;

	i = -1;
	count_doubles = 0;
	count_singles = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			count_singles++;
		if (str[i] == '\"')
			count_doubles++;
	}
	if (count_doubles % 2 || count_singles % 2)
		return (1);
	return (0);
}

int	count_elements(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (check_quotes(str))
		return(write(2, "problem with quotes\n", 21), 1);
	while (str[i])
	{
		while (is_whitespace(str[i]) && str[i])
			i++;
		if (str[i] == '\'')
			while (str[++i] != '\'' && str[i])
				;
		else if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		else
			while(!is_whitespace(str[i]) && str[i])
				i++;
		count++;
	}
	return (count);
}

//creates substring until certain Character
char	*make_substr(char *str, char *delimiter)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{

	}
}

//split input string into tokens and characterize them (hopefullly)
char **token_splitter(char *str)
{
	char	**ret;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ret = (char **) ft_calloc((count_elements(str) + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		
	}
}