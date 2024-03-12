#include "../../minishell.h"
#include "parse.h"

char	*ft_string_insert(char *str, char *in, int idx, int varlen)
{
	char	*ret;
	char	*intro;
	char	*outro;
	char	*first;

	if (!str || !in)
		return (str);
	intro = ft_strndup(str, idx);
	outro = ft_strdup(str + idx + varlen + 1);
	first = ft_strjoin(intro, in);
	ret = ft_strjoin(first, outro);
	if (idx)
	{
		free(intro);
		free(first);
	}
	free(outro);
	free(str);
	return (ret);
}

char	*find_var_name(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	if (!ft_isalnum(str[i]) && !is_char(str[i], "_"))
		return (NULL);
	while (str[i + j] && !is_char(str[i + j], "\n\t\v \r\f$\"\'") && str[i + j])
		j++;
	return (ft_strndup(&str[i], j));
}

char	*get_val(char *var, t_bigshell *data)
{
	t_env	*curr;

	if (!data)
		return (printf("EYYYY WHERES MY VAL"), NULL);
	curr = data->env;
	while (curr)
	{
		if (ft_strnstr(curr->str, var, ft_strlen(var)))
			break ;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	return (ft_strchr(curr->str, '=') + 1);
}

//expands $-variable
char *expand(char *str, t_bigshell *data)
{
	char	*here;
    char	*var;
	char	*val;
	char	*new;

	printf("TO EXPAND: %s\n", str);
	int i = 0;
	while (1)
	{
		while (str[i] && str[i] != '$')
		{
			if (str[i] == '\'')
				while (str[i] && str[i] != '\'')
					i++;
			i++;
		}
		here = ft_strchr(&str[i], '$');
		if (here)
		{
			var = find_var_name(here);
			if (!var)
				return (printf("NOT A LEGIT VARIABLE NAME\n"), str);
			//val = getenv(var);
			val = get_val(var, data);
			if (!val)
				return (free(var),str);
			printf("val = %s", val);
			new = ft_string_insert(str, val, here - str, ft_strlen(var));
			free(var);
			str = new;
		}
		else
			break ; 
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
