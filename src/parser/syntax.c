#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

int	skip_quotes(char *str,int *i,char c)
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
	if (is_char(str[*i], "<>|"))
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


int	check_syntax(char *str)
{
	int		i;
	int		check;

	i = 0;
	check = 1;
	while (str[i] && check)
	{
		if (is_char(str[i], "\'\"|<>"))
			check = check_specials(str, &i);
		else
			i++;
	}
	if (!check)
		(write(2, "SYNTAX ERROR\n", 14));
	return (check);
}