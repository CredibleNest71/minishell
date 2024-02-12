#include "../minishell.h"
#include "parse.h"

void	clean_heredoc(t_token *token)
{

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

/*
t_command   *transform(t_token *list)
{
	t_command *cmd;
	//classify token type
	classify(list);
	mark_commands(list);
	clean_list(list);
	cmd = create_commands(list);
}
*/