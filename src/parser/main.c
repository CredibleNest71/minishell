
#include "../../minishell.h"
#include "parse.h"
#include "../../libft/libft.h"



//RETURNS:
// 1 = all good
// 0 = not ended
// -1 = error
int	check_heredoc_fin(char *str)
{
	int		j;
	int		i;
	char	*del;

	i = 2;
	j = 0;
	skip_white_space(str, &i);
	skip_chars(&str[i], &j);
	if (!str[i])
		return (write(2, "ERROR CHECKING HEREDOC: missing delimiter\n", 24), -1);
	del = ft_strndup(&str[i], j);
	printf("::check_heredoc::delimiter:%s\n", del);
	if (!del)
		return (write(2, "ERROR CHECKING HEREDOC\n", 24), -1);
	if (ft_strnstr(str + i + j, del, 10000))
		return (free(del), 1);
	else
		return (free(del), 0);
}

static int check_fin(char *input)
{
	int		i;
	int 	fin;
	char	c;
	i = 0;
	fin = 1;
	c = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			fin *= -1;
			c = 0;
		}
		else if (!c && (input[i] == '\"' || input[i] == '\''))
		{
			fin *= -1;
			c = input[i];
		}
		if (!strncmp(&input[i], "<<", 2) && fin > 0)
			if (check_heredoc_fin(&input[i]) <= 0)
				return (check_heredoc_fin(&input[i]));
		i++;
	}
	return (fin > 0 ? 1 : 0);
}

int main(void)
{
	char    	*input;
	char		*temp;
	char		*temp2;
	t_token		*parsed;
	t_command	*cmds;
	int			finished;
	t_bigshell	data;
	while (1)
	{
		finished = 0;
		input = ft_strdup("");
		printf("\nEnter commands:");
		while (!finished)
		{
			temp = input;
			temp2 = readline(">");
			input = ft_strjoin(input, temp2);
			free(temp);
			free(temp2);
			finished = check_fin(input);
			if (finished < 0)
				return (write(2, "ERROR\n", 7));
			break ;
		}
		cmds = parse(input, &data); //
		print_cmds(cmds);
		delete_command_list(cmds);
		free(input);
		break ;
	}
	return (0);
}
