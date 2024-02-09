
#include "../minishell.h"
#include "parse.h"
#include "../libft/libft.h"

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