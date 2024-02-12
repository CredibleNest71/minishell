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

//compares given character to list of characters
// returns 1 if theres a match
int	is_char(char c, char *chars)
{
	int		i;

	i = -1;
	while (chars[++i])
		if (chars[i] == c)
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
		while (is_char(str[i], "\n\t\v \r\f") && str[i])
			i++;
		if (str[i] == '\'')
			while (str[++i] != '\'' && str[i])
				;
		else if (str[i] == '\"')
			while (str[++i] != '\"')
				;
		else
			while(!is_char(str[i], "\n\t\v \r\f") && str[i])
				i++;
		count++;
	}
	return (count);
}

//creates substring until certain Character
//allocates memory
char	*make_substr(char *str, char *delimiter)
{
	int	i;
	int	j;
	char *ret;

	if (!str || !delimiter)
		return (NULL);
	i = 0;
	while (str[i] && !is_char(str[i], delimiter))
		i++;
	ret = (char *) ft_calloc (i + 1, 1);
	if (!ret)
		return (write(2, "ERROR ALLOCATING\n", 18), NULL);
	j = -1;
	while (str[++j] && j < i + 1)
		ret[j] = str[j];
	if (is_char(ret[j - 1], delimiter))
		ret[j - 1] = 0;
	return (ret);
}

//split input string into tokens and characterize them (hopefullly)
char **token_splitter(char *str)
{
	char	**ret;
	char	*dels;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	ret = (char **) ft_calloc((count_elements(str) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (str[i] && i < ft_strlen(str))
	{
		dels = "\n\t\v \r\f";
		while (str[i] && is_char(str[i], "\n\t\v \r\f"))
			i++;
		if (str[i] == '\"')
			dels = "\"";
		else if (str[i] == '\'')
			dels = "\'";
		if (is_char(str[i], "\"\'"))
			i++;
		ret[j++] = make_substr(&str[i], dels);
		while (str[i] && !is_char(str[i], dels))
			i++;
		i++;
	}
	return (ret);
}

t_token	**tokenize(char **elements)
{
	t_token **ret;
	int		i;
	int		j;

	i = 0;
	if (!elements)
		return (NULL);
	while (elements[i])
		i++;
	ret = (t_token **) ft_calloc (i + 1, sizeof(t_token *));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = tokenify(elements[j]);
		j++;
	}
	free(elements);
	return (ret);
}

int	find_commands(t_token **tokens)
{
	int	i;
	int	cmds;

	cmds = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == (enum type) ARG && !i)
		{
			cmds++;
			tokens[i]->type = (enum type) CMD;
		}
		else if (tokens[i - 1]->type == (enum type) NEX)
		{
			tokens[i]->type = (enum type) CMD;
			cmds++;
		}
		i++;
	}
	return (cmds);
}

void mark_path(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == (enum type) DIR)
			tokens[i + 1]->type = (enum type) PATH;
		i++;
	}
}

void	set_redirections(t_token **tokens, t_command *ret)
{
	int	dir;

	dir = 0;
	ret->input = NULL;
	while (tokens[dir])
	{
		if (tokens[dir]->type == (enum type) DIR)
			break ;
		dir++;
	}
	if (!tokens[dir])
		return ;
	if (tokens[dir + 1]->type == (enum type) PATH)
		tokens[dir + 1]->dir = tokens[dir]->str;
	if (tokens[dir]->str == "<" || tokens[dir]->str == "<<")
		ret->input = tokens[dir + 1];
	else if (tokens[dir]->str == ">" || tokens[dir]->str == ">>")
		ret->output = tokens[dir + 1];
	printf("IN%s", ret->input->str);
	return ;
}

int	count_args(t_token **tokens)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (tokens[i] && tokens[i]->type != (enum type) NEX)
	{
		if (tokens[i]->type == (enum type) ARG)
			count++;
		i++;
	}
	return (count);
}

//finds Arguments typed "ARG" belonging to the command pointed to
// returns argument array
t_token	**make_arg_list(t_token **tokens)
{
	int			args_amount;
	t_token		**args;
	int			i;
	int			j;

	args_amount = count_args(tokens);
	args = (t_token **) ft_calloc (sizeof(t_token *), args_amount);
	if (!args)
		return (NULL);
	i = 0;
	j = 0;
	while (j < args_amount && tokens[i])
	{
		if (tokens[i]->type == (enum type) ARG)
			args[j++] = tokens[i];
		i++;
	}
	return (args);
}

t_command	*make_command(t_token **tokens)
{
	int			i;
	t_command	*ret;

	ret = (t_command *) ft_calloc (sizeof(t_command), 1);
	if (!ret)
		return (NULL);
	ret->cmd = tokens[0];
	mark_path(tokens);
	set_redirections(tokens, ret);
	ret->args = make_arg_list(tokens);

	return (ret);
}

t_command **commandlistmaker(char *str)
{
	t_command	**ret;
	t_token		**tokenized;
	char		**seperated;
	int			cmds;
	int			i;

	seperated = token_splitter(str);
	tokenized = tokenize(seperated);
	cmds = find_commands(tokenized);
	ret = (t_command **) ft_calloc (sizeof (t_command), cmds + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (*tokenized)
	{
		if ((*tokenized)->type == (enum type) CMD)
		ret[i++] = make_command(&(*tokenized));
		tokenized++;
	}
	return (ret);
}
