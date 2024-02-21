#include "../minishell.h"
#include "parse.h"

char	*ft_string_insert(char *str, char *in, int idx, int varlen)
{
	char	*ret;
	char	*intro;
	char	*first;

	intro = ft_strndup(str, idx);
	first = ft_strjoin(intro, in);
	ret = ft_strjoin(first, &str[idx + varlen + 1]);
	free(intro);
	free(first);
	return (ret);
}

char	*find_var_name(char *str)
{
	int	i;
	int	j;
	char *name;
	j = 0;
	i = 0;

	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	while (!is_char(str[i + j], "\n\t\v \r\f") && str[i + j])
		j++;
	return (ft_strndup(&str[i], j));
}

//expands $-variable
char *expand(char *str)
{
	int		i;
    char	*var;
	char	*val;
	char	*new;

	i = 0;
	while (i < ft_strlen(str) && str[i])
	{
		if (str[i] == '$')
		{
			var = find_var_name(str);
			if (!var)
				return (printf("not found"), str);
			val = getenv(var);
			if (!val)
				return (free(var),str);
			new = ft_string_insert(str, val, i, ft_strlen(var));
			i += ft_strlen(val);
			free(var);
			//free(str);
			str = new;
		}
		i++;
	}
	return (str);
}


// int main ()
// {
// 	char	*test;
// 	//test =  expand("this is  $RUBY_HOME $RUBY_HOME $RUBY_HOME testtesttesttest\n");
// 	test = expand(readline("pls give input"));
// 	printf("%s\n", test);
// 	free(test);
// }
