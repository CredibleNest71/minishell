#include "../minishell.h"
#include "parse.h"

t_token	*expand_token(t_token *token)
{
	char	*temp;
	if (token->type == (e_type) ARG)
	{
		temp = token->str;
		token->str = expand(temp);
	}
	return (token);
}

void	clean_heredoc(t_token *token)
{
	char	*new;

	int	j;
	int	i;

	i = 0;
	j = 0;
	printf("\n:clean_heredoc: \"%s\"", token->str);
	while (is_char(token->str[i], "\n\t\v \r\f<"))
		i++;
	while (!is_char(token->str[i], "\n\t\v \r\f"))
		i++;
	i++;

	new = (char *) malloc (ft_strlen(&(token->str[i])));
	if (!new)
		return ;
	while (token->str[i])
		new[j++] = token->str[i++];
	while (!is_char(new[--j], "\n\t\v \r\f") && j)
		j--;
	new[j] = 0;
	free(token->str);
	token->str = new;
	printf("\n:clean_heredoc: \"%s\"", token->str);
}

void	clean_token(t_token *token)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!token)
		return ;
	if (token->type == (e_type) CMD || token->type == (e_type) PIPE)
		return ;
	while (is_char(token->str[i], "<>") && token->str[i])
		i++;
	while (is_char(token->str[i], "\n\t\v \r\f") && token->str[i])
		i++;
	if (token->type == (e_type) HEREDOC)
		return (clean_heredoc(token));
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

	curr = list;
	if (curr->type == (e_type) ARG)
		curr->type = (e_type) CMD;
	while (curr)
	{
		if (curr->type == (e_type) PIPE && curr->next && curr->next->type == (e_type) ARG)
			curr->next->type = (e_type) CMD;
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
			replace_or_append(&ret->args, expand_token(temp));
		else if (temp->type == (e_type) IN)
			replace_or_append(&ret->input, temp);
		else if (temp->type == (e_type) OUT)
			replace_or_append(&ret->output, temp);
		else if (temp->type == (e_type) APP)
			replace_or_append(&ret->append, temp);
		else if (temp->type == (e_type) HEREDOC)
			replace_or_append(&ret->heredoc, temp);
		freeme = temp;
		temp = temp->next;
		free(freeme->str);
		free(freeme);
		if (temp && temp->type == (e_type) CMD)
			break ;
	}
	return (temp);
}

t_command	*create_commands(t_token *token)
{
	t_command	*og = NULL;
	t_command	*ret = NULL;
	t_command	*prev = NULL;

	while (token)
	{
		if (token->type == (e_type) CMD)
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
			printf("cmd->cmd = %s\n", ret->cmd->str);
		}
		//token = token->next;
	}
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
