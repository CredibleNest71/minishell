
#include "../minishell.h"
#include "parse.h"
#include "../libft/libft.h"

void	token_append(t_token *lst, t_token *token)
{
	if (!token)
		return ;
	if (!lst)
		lst = token;
	while (lst->next)
		lst = lst->next;
	lst->next = token;
}

//duplicates, next->NULL
t_token	*token_dup(t_token *token)
{
	t_token	*dup;

	dup = (t_token *) ft_calloc (sizeof(t_token), 1);
	if (!dup)
		return (NULL);
	dup->str = token->str;
	dup->type = token->type;
	return (dup);
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*ans;

	i = 0;
	if (n <= 0)
		return (0);
	ans = malloc(n + 1);
	if (!ans)
		return (0);
	while (s[i] && i < n)
	{
		ans[i] = s[i];
		i++;
	}
	ans[i] = 0;
	return (ans);
}

int	is_char(char c, char *chars)
{
	int		i;

	i = -1;
	while (chars[++i])
		if (chars[i] == c)
			return (1);
	return (0);
}