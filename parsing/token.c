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
