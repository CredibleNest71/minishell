#include "../minishell.h"
#include "parse.h"

char	*ft_string_insert(char *str, char *in, int idx)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(str) + ft_strlen(in) + 1;
	ret = (char *) ft_calloc(len, 1);
	if (!ret)
		return (NULL);
	while (i < idx)
		ret[i] = str[i++];
	while (in[j])
		ret[i++] = in[j++];
	while (str[i])
		ret[i + j] = str[i++];
	//free(str);
	//free(in);
	printf(":string_insert_return:	%s\n", ret);
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
	printf("str i to copy:	%s\n", &str[i]);
	return (ft_strndup(&str[i], j));
}

//expands $-variable
char *expand(char *str)
{
	int		i;
    char	*var;
	char	*val;

	i = 0;
	while (i < ft_strlen(str) && str[i])
	{
		if (str[i] == '$')
		{
			var = find_var_name(str);
			if (!var)
				return (printf("not found"), str);
			val = getenv(var);
			printf("val:	%s\n", val);
			if (!val)
				return (str);
			str = ft_string_insert(str, val, i);
			i += ft_strlen(val);
		}
		i++;
	}
	printf(":expand_return:	%s\n", str);
	return (str);
}


int main ()
{
	printf("%s\n", expand("this is $RUBY_HOME YES\n"));
}
