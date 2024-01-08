#include "../minishell.h"

int	number_of_cmd(char **in)
{
	int		i;
	int		j;
	int		count;
	char	*seperators[] = {"|", "<", ">", ">>", "<<"};

	i = 0;
	count = 0;
	while (++i)
	{
		j = -1;
		while (++j)
			if (!ft_strncmp(in[i], seperators[j], 100))
				count++;
	}
	return (count + 1);
}

t_command   *parse(char *in)
{
	char	**ret;
	int		num_cmd;

	ret = ft_split(in, ' ');
	if (!ret)
		return (NULL);
	num_cmd = number_of_cmd(ret);
}