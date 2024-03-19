#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

t_token **expand_no_quotes(t_token *prev, t_token *curr, t_bigshell *data)
{
	char	*expanded;
	
	expanded = expand(curr->str, data);
	// now split into tokens (no quotes)
	// remember join flag (last token inherits)
}

void    launch_expansion(t_token *prev, t_token *curr, t_bigshell *data)
{
	if (curr->str[0] == '\'')
		return ;
	else if (curr->str[0] == '\"')
		expand(curr->str, data);
	else if (curr->str[0] == '$')
		expand_no_quotes(prev, curr, data);
	return ;
}

t_token **expander(t_token **list, t_bigshell *data)
{
    t_token *curr;
    t_token *prev;

    curr = *list;
    prev = NULL;
    while(curr)
    {
        if (ft_strchr(curr->str, '$'))
            launch_expansion(prev, curr, data);

        prev = curr;
        curr = curr->next;
    }
}