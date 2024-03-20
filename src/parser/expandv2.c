#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

t_token	*make_t(char *str)
{
	t_token	*token;

	if (!str)
		return (NULL);
	token = (t_token *) ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->str = str;
	token->type = (e_type) ARG;
	return (token);
}

t_token **split_to_token(char **split, int join)
{
	t_token **ret;
	t_token *new;
	int	i;

	i = 0;
	ret = (t_token **) ft_calloc (sizeof(t_token *), 1);
	while (split[i])
	{
		new = make_t(split[i]);
		token_list_add(ret, new);
		i++;
	}
	if (join)
		new->connected = 1;
	return (ret);
}

void	insert_tokenlist(t_token *prev, t_token *curr, t_token **addlist)
{
	t_token	*next;
	t_token	*last;

	next = curr->next;
	prev->next = *addlist;
	last = ft_tokenlast(*addlist);
	last->next = next;
	free(curr->str);
	free(curr);
}


void	expand_no_quotes(t_token *prev, t_token *curr, t_bigshell *data)
{
	char	*expanded;
    char    **split;
	t_token	**addlist;
	int		join;
	
	expanded = expand(curr->str, data);
	join = 0;
	if (is_char(expanded[ft_strlen(expanded) - 1], "\n\t\v \r\f"))
		join = 1;
    split = ft_split(expanded, ' ');
	addlist = split_to_token(split, join);
	insert_tokenlist(prev, curr, addlist);

}

char	*remove_quotes(char *str)
{
	int		len;
	char	*ret;

	if (!str)
		return (NULL);
	if (!is_char(str[0], "\"\'"))
		return (str);
	len = ft_strlen(str);
	ret = ft_strndup(&str[1], len - 2);
	free(str);
	return (ret);
}


void    launch_expansion(t_token *prev, t_token *curr, t_bigshell *data)
{
	if (curr->str[0] == '\'')
	{
		curr->str = remove_quotes(curr->str);
		return ;
	}
	else if (curr->str[0] == '\"')
	{
		curr->str = remove_quotes(curr->str);
		expand(curr->str, data);
	}
	else if (curr->str[0] == '$')
		expand_no_quotes(prev, curr, data);
	return ;
}

void	join(t_token **list)
{
	t_token	*curr;
	t_token	*next;
	char	*jstr;

	curr = *list;
	while (curr)
	{
		next = curr->next;
		if (curr->connected && next && next->type == (e_type) ARG)
		{
			jstr = ft_strjoin(curr->str, next->str);
			free(curr->str);
			free(next->str);
			curr->str = jstr;
			curr->connected = next->connected;
			curr->next = next->next;
			free(next);
			continue ;
		}
		curr = curr->next;
	}
}


t_token **expander(t_token **list, t_bigshell *data)
{
    t_token *curr;
    t_token *prev;
    t_token *next;

    curr = *list;
    prev = NULL;
    while(curr)
    {
		next = curr->next;
        if (ft_strchr(curr->str, '$'))
            launch_expansion(prev, curr, data);
		else
			curr->str = remove_quotes(curr->str);
        prev = curr;
        curr = next;
    }
	join(list);
	return (list);
}