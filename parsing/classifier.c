#include "../minishell.h"
#include "parse.h"

void	clean_heredoc(t_token *token)
{
	char	*new;

	int	j;
	int	i;

	i = 0;
	j = 0;
	while (!is_char(token->str[i], "\n\t\v \r\f"))
		i++;
	new = (char *) ft_calloc (ft_strlen(&(token->str[i])) + 1, 1);
	if (!new)
		return ;
	while (token->str[i])
		new[j++] = token->str[i++];
	while (!is_char(new[j], "\n\t\v \r\f"))
		new[j--] = 0;
	free(token->str);
	token->str = new;
}


void	clean_token(t_token *token)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (token->type == (e_type) CMD || token->type == (e_type) PIPE)
		return ;
	while (is_char(token->str[i], "<>") && token->str[i])
		i++;
	while (is_char(token->str[i], "\n\t\v \r\f") && token->str[i])
		i++;
	if (token->type == (e_type) HEREDOC)
		clean_heredoc(token);
	if (is_char(token->str[i], "\"\'"))
		i++;
	new = (char *) ft_calloc (ft_strlen(token->str) + 1 - i, 1);
	if (!new)
		return ;
	while (token->str[i])
		new[j++] = token->str[i++];
	if (is_char(new[j - 1], "\"\'"))
		new[j - 1] = 0;
	free(token->str);
	token->str = new;
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
}

void	mark_commands(t_token *list)
{
	t_token *curr;

	curr = list;
	if (curr->type == (e_type) ARG)
		curr->type = (e_type) CMD;
	while (curr)
	{
		if (curr->type == (e_type) PIPE && curr->next->type == (e_type) ARG)
			curr->next->type = (e_type) CMD;
		curr = curr->next;
	}
}

void	fill_command(t_command *ret, t_token *temp)
{
	if (!ret || !temp)
		return ;
	while (temp)
	{
		printf("\n:fill_command: %s", temp->str);
		if (temp->type == (e_type) CMD)
			ret->cmd = temp;
		else if (temp->type == (e_type) ARG)
		{
			if (!ret->args)
				ret->args = token_dup(temp);
			else
				token_append(ret->args, token_dup(temp));
		}
		else if (temp->type == (e_type) IN)
			ret->input = temp;
		else if (temp->type == (e_type) OUT)
			ret->output = temp;
		else if (temp->type == (e_type) APP)
			ret->append = temp;
		else if (temp->type == (e_type) HEREDOC)
			ret->heredoc = temp;
		temp = temp->next;
		if (temp && temp->type == (e_type) CMD)
			break ;
	}
}

t_command	*create_commands(t_token *token)
{
	t_command	*og;
	t_command	*ret;
	t_command	*prev;
	int			arg_num;

	ret = (t_command *) ft_calloc (sizeof(t_command), 1);
	if (!ret)
		return (NULL);
	og = ret;
	fill_command(ret, token);
	/*
	while (token)
	{
		if (token->type == (e_type) CMD)
		{
			prev = ret;
			ret = (t_command *) ft_calloc (sizeof(t_command), 1);
			if (!ret)
				return (NULL);
			prev->next = ret;
			fill_command(ret, token);
		}
		token = token->next;
	}
	*/
	return (og);
}

t_command   *transform(t_token *list)
{
	t_token		*temp;
	t_command	*cmd;

	temp = list;
	classify(list);
	mark_commands(list);
	while (temp)
	{
		clean_token(temp);
		temp = temp->next;
	}
	cmd = create_commands(list);
	return (cmd);
}
