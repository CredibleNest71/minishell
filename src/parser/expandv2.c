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

/*
static void	set_connects(char *str, int *pre, int *post)
{
	int	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (is_char(str[0], " "))
		*pre = 0;
	else
		*pre = 1;
	if (is_char(str[len - 1], " "))
		*post = 0;
	else
		*post = 1;
}
*/
t_token **split_to_token(char *expanded)
{
	t_token **ret;
	t_token *new;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(expanded, ' ');
	ret = (t_token **) ft_calloc (sizeof(t_token *), 1);
	while (split[i])
	{
		new = make_t(split[i]);
		token_list_add(ret, new);
		i++;
	}
	printf("split_to_token::expanded: %s\nis_chare:xpanded[0]: '%c'", expanded, expanded[0]);
	if (is_char(expanded[0], SPACE3))
		(*ret)->distanced = 1;
	if (!is_char(expanded[ft_strlen(expanded) - 1], SPACE3))
		new->connected = 1;
	return (ret);
}

void	insert_tokenlist(t_token **list, t_token *prev, t_token *curr, t_token **addlist)
{
	t_token	*next;
	t_token	*last;

	next = curr->next;
	if (prev)
	{
		prev->next = *addlist;
		(*addlist)->prev = prev;
	}
	else
		*list = *addlist;
	last = ft_tokenlast(*addlist);
	last->next = next;
	next->prev = last;
	for (t_token *temp = *list; temp; temp = temp->next)
		printf("insert:: %s\n", temp->str);
}

void	expand_no_quotes(t_token **list, t_token *prev, t_token *curr, t_bigshell *data)
{
	char	*expanded;
	t_token	**addlist;
	
	expanded = expand(curr->str, data);
	addlist = split_to_token(expanded);
	insert_tokenlist(list, prev, curr, addlist);
	for (t_token *temp = *list; temp; temp = temp->next)
		printf("expandnoquotes:: %s\n", temp->str);
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


void    launch_expansion(t_token **list, t_token *prev, t_token *curr, t_bigshell *data)
{
	if (curr->str[0] == '\'')
	{
		curr->str = remove_quotes(curr->str);
		return ;
	}
	else if (curr->str[0] == '\"')
	{
		curr->str = remove_quotes(curr->str);
		curr->str = expand(curr->str, data);
	}
	else if (curr->str[0] == '$')
		expand_no_quotes(list, prev, curr, data);
	else
		expand_no_quotes(list, prev, curr, data);
	for (t_token *temp = *list; temp; temp = temp->next)
		printf("launch:: %s\n", temp->str);
	return ;
}

static	void mark_join(t_token **list)
{
	t_token	*curr; 

	curr = *list;
	while (curr)
	{
		if (curr->prev)
		{
			printf("curr: %s\n prev: %s\n", curr->str, curr->prev->str);
			if (curr->distanced)
				curr->prev->connected = 0;
		}
		curr = curr->next;
	}
}

void	join(t_token **list)
{
	t_token	*curr;
	t_token	*next;
	char	*jstr;

	curr = *list;
	mark_join(list);
	for (t_token *temp = *list; temp; temp = temp->next)
		printf("prejoin:: %s(con%d/dis%d)\n", temp->str, temp->connected, temp->distanced);
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
	for (t_token *temp = *list; temp; temp = temp->next)
		printf("post:: %s(%d)\n", temp->str, temp->connected);
}


t_token **expander(t_token **list, t_bigshell *data)
{
	t_token *curr;
	t_token *prev;

	curr = *list;
	prev = NULL;
	while(curr)
	{
		if (curr->type == (e_type) HEREDOC)
			;
		else if (ft_strchr(curr->str, '$'))
			launch_expansion(list, prev, curr, data);
		else
			curr->str = remove_quotes(curr->str);
		prev = curr;
		curr = curr->next;
    }
	join(list);
	return (list);
}
 