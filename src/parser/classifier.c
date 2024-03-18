#include "../../minishell.h"
#include "parse.h"
#include <string.h>

t_token	*expand_token(t_token *token, t_bigshell *data)
{
	char	*temp;
	temp = token->str;
	printf("not expanded: %s\n", token->str);
	token->str = expand(temp, data);
	printf("expanded: %s\n", token->str);
	return (token);
}

void	clean_heredoc(t_token *token)
{
	char	*new;

	int	j;
	int	i;

	i = 0;
	j = 0;
	//printf("\n:clean_heredoc: \"%s\"", token->str);
	while (is_char(token->str[i], "\n\t\v \r\f<"))
		i++;
	// while (!is_char(token->str[i], "\n\t\v \r\f"))
	// 	i++;
	// i++;
	j = findarg(&token->str[i]);
	new = ft_strndup(&token->str[i], j);
	// new = (char *) malloc (ft_strlen(&(token->str[i])));
	// if (!new)
	// 	return ;
	// while (token->str[i])
	// 	new[j++] = token->str[i++];
	// while (!is_char(new[--j], "\n\t\v \r\f") && j)
	// 	j--;
	// new[j] = 0;
	token->delimiter = new;
	free(token->str);
	token->str = NULL;
	//printf("\n:clean_heredoc:del: %s", token->delimiter);
}

void	clean_token(t_token *token, t_bigshell *data)
{
	char	*new;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	if (!token)
		return ;
	printf("::clean_token::%s\n", token->str);
	token = expand_token(token, data);
	if (token->type == (e_type) PIPE)
		return ;
	while (is_char(token->str[i], "<>") && token->str[i])
		i++;
	while (is_char(token->str[i], "\n\t\v \r\f") && token->str[i])
		i++;
	if (token->type == (e_type) HEREDOC)
		return (clean_heredoc(token));
	// if (is_char(token->str[i], "\"\'"))
	// 	i++;
	new = (char *) ft_calloc (ft_strlen(token->str) + 1 - i, 1);
	if (!new)
		return ;
	while (token->str[i])
	{
		if (is_char(token->str[i], "\"\'"))
			c = token->str[i];
		if (is_char(c, "\"\'") && ft_strchr(&token->str[i], c))
		{
			i++;
			while (token->str[i] != c)
				new[j++] = token->str[i++];
			i++;
		}
		new[j++] = token->str[i++];
	}
	if (is_char(new[j - 1], "\"\'"))
		new[j - 1] = 0;
	free(token->str);
	token->str = new;
}

int	check_pipes(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp)
	{
		if (temp->type == (e_type) PIPE && !temp->next)
			return (0);
		if (temp->type == (e_type) PIPE && temp->next->type == (e_type) PIPE)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	classify(t_token *list)
{
	t_token	*curr;

	curr = list;
	while (curr)
	{
		if (!strncmp(curr->str, "<<", 2))
			curr->type = (enum type) HEREDOC;
		else if (!strncmp(curr->str, ">>", 2))
			curr->type = (enum type) APP;
		else if (!strncmp(curr->str, "<", 1))
			curr->type = (enum type) IN;
		else if (!strncmp(curr->str, ">", 1))
			curr->type = (enum type) OUT;
		else if (!strncmp(curr->str, "|", 1))
			curr->type = (enum type) PIPE;
		else
			curr->type = (enum type) ARG;
		curr = curr->next;
	}
	if (!check_pipes(list))
		write(2, "SYNTAX ERROR\n", 14);
}

void	mark_commands(t_token *list)
{
	t_token *curr;
	int		need_cmd;

	need_cmd = 1;
	curr = list;
	while (curr)
	{
		if (need_cmd && curr && curr->type == (e_type) ARG)
		{
			curr->type = (e_type) CMD;
			need_cmd = 0;
		}
		if (curr->type == (e_type) PIPE)
			need_cmd = 1;
		curr = curr->next;
	}
}

static void	replace_or_append(t_token **list, t_token *token)
{
	if (*list)
		token_append(*list, token_dup(token));
	else
		*list = token_dup(token);
}

t_token	*fill_command(t_command *ret, t_token *temp)
{
	if (!ret || !temp)
		return (NULL);
	t_token	*freeme;

	while (temp)
	{
		if (temp->type == (e_type) CMD)
			ret->cmd = token_dup(temp);
		else if (temp->type == (e_type) ARG)
			replace_or_append(&ret->args, temp);
		else if (temp->type == (e_type) IN)
			replace_or_append(&ret->input, temp);
		else if (temp->type == (e_type) OUT)
			replace_or_append(&ret->output, temp);
		else if (temp->type == (e_type) APP)
			replace_or_append(&ret->output, temp);
		else if (temp->type == (e_type) HEREDOC)
			replace_or_append(&ret->input, temp);
		freeme = temp;
		temp = temp->next;
		free(freeme->str);
		free(freeme);
		if (!ret->cmd)
			continue ;
		if (temp && temp->type == (e_type) PIPE)
			break ;
	}
	return (temp);
}

t_command	*create_commands(t_token *token)
{
	t_command	*og = NULL;
	t_command	*ret = NULL;
	t_command	*prev = NULL;
	int			i = 0;

	while (token)
	{
		if (!i++ || token->type == (e_type) PIPE)
		{
			prev = ret;
			ret = (t_command *) ft_calloc (sizeof(t_command), 1);
			if (!ret)
				return (NULL);
			if (prev)
				prev->next = ret;
			else
				og = ret;
			token = fill_command(ret, token);
			if (!ret->cmd)
			{
				return (delete_command_list(og), write(2, "missing command", 16), NULL);
			}
		}
		//token = token->next;
	}
	return (og);
}
////////////////////////////////////////////////////////////////
void	unify(t_token *og, t_token *ad)
{
	t_token	*cont;
	t_token	*temp;

	cont = og->next;
	free(og->str);
	og->str = ad->str;
	og->next = ad->next;
	temp = ft_tokenlast(ad);
	temp->next = cont;
}

//expands token strings, creates new tokens if necessary
void	expand_token_list(t_token *list, t_bigshell *data)
{
	t_token	*temp;
	t_token	*new;

	temp = list;
	while (temp)
	{
		if (ft_strchr(temp->str, '$'))
		{
			expand(temp->str, data);
			new = parse_tokens(temp->str);
			for (t_token *tp = new; tp; tp = tp->next)
				printf("new token: %s\n", tp->str);
			unify(temp, new);
		}
		temp = temp->next;
	}
}
////////////////////////////////////////////////////////////////

t_command   *transform(t_token *list, t_bigshell *data)
{
	t_token		*temp;
	t_command	*cmd;

	temp = list;
	expand_token_list(list, data);
	classify(list);
	while (temp)
	{
		clean_token(temp, data);
		temp = temp->next;
	}
	mark_commands(list);
	cmd = create_commands(list);
	return (cmd);
}
