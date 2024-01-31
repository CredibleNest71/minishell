#include "../minishell.h"
#include "parse.h"

int	is_char(char c, char *chars)
{
	int		i;

	i = -1;
	while (chars[++i])
		if (chars[i] == c)
			return (1);
	return (0);
}

void	skip_quotes(char *str, int *idx)
{
	if (str[*idx] == '\'')
	{
		*idx++;
		while (str[*idx] && str[*idx] != '\'')
			*idx++;
	}
	if (str[*idx] == '\"')
	{
		*idx++;
		while (str[*idx] && str[*idx] != '\"')
			*idx++;
	}
	return ;
}

//checks for unclosed quotes
int check_quotes(char *str)
{
	int i;
	int open;

	i = 0;
	open = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			while (str[i] != '\"' && str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			while (str[i] != '\'' && str[i])
				i++;
		}
		if (!str[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_inandout(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_quotes(&str[i], &i);
		if (is_char(str[i], "<>"))
		{
			i++;
			while (is_char(str[i], "\n\t\v \r\f") && str[i])
				i++;
		}
		if (!ft_isalnum(str[i]) && !is_char(str[i], "\'\""))
			return (1);
		i++;
	}
	return (0);
}

int	check_heredoc(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (is_char(str[i], "\n\t\v \r\f") && str[i])
		i++;
	while (!is_char(str[i + j], "\n\t\v \r\f") && str[i])
		j++;
	char delimiter[j];
	j = 0;
	while (!is_char(str[i], "\n\t\v \r\f") && str[i])
		delimiter[j++] = str[i++];
	delimiter[j] = 0;
	if (ft_strnstr(&str[i], delimiter, 10000))
		return (0);
	return (1);
}

int	check_docandapp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		skip_quotes(&str[i], &i);
		if (!strncmp(&str[i], "<<", 2))
		{
			if (check_heredoc(&str[i + 2]))
				return (1);
		}
		else if (!strncmp(&str[i], ">>", 2))
		{
			i += 2;
			while (is_char(str[i], "\n\t\v \r\f") && str[i])
				i++;
		}
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int check_redirs(char *str)
{
	int	check;

	check = check_inandout(str);
	check += check_docandapp(str);
}

int	check_syntax(char *str)
{
	check_quotes(str);
	check_redirs(str);
}

int main()
{return 0;}