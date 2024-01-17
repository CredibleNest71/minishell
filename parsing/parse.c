#include "../minishell.h"

//compares string to seperating operators
int	is_seperator(char *str)
{
	int	i;
	char	*seperators[] = {"|", "<", ">", ">>", "<<", NULL};
	
	i = 0;
	if (!str)
		return (0);
	while (i < 6 && seperators[i])
	{
		if (!ft_strncmp(str, seperators[i++], 3))
			return (1);
	}
	return (0);
}

//returns number of commands
int	number_of_cmd(char **in)
{
	int		i;
	int		j;
	int		count;
	char	*seperators[] = {"|", "<", ">", ">>", "<<", NULL};

	i = -1;
	count = 0;
	while (in[++i])
	{
		j = -1;
		//printf("%s\n", in[i]);
		while (++j)
			if (!ft_strncmp(in[i], seperators[j], 2))
				count++;
	}
	return (count + 1);
}

//creates instance of command struct and appends it to the linked
//list if the first argument is another instance of a command struct
//returns the newly added element
t_command	*create_command_struct(t_command *prev, char **tokens)
{
	t_command	*ret;
	int			i;

	i = 0;
	ret = (t_command *) malloc(sizeof(t_command));
	if (prev)
		prev->next = ret;
	ret->next = NULL;
	ret->cmd = *tokens;
	while (tokens[i])
	{
		if (is_seperator(tokens[i]))
		{
			ret->nexus = tokens[i];
			break ;
		}
		i++;
	}
	ret->args = &(tokens[1]);
	ret->arg_num = i;
	return (ret);
}

//creates a linked list of command structs with the given tokens
t_command *make_command_list(int num_cmd, char **tokens)
{
	t_command	*ret;
	t_command	*temp;
	int			i;
	int			j;

	ret = (t_command *) malloc(sizeof(t_command));
	i = 0;
	j = 0;
	if (!num_cmd || !ret)
		return (NULL);
	ret->next = NULL;
	temp = ret;
	while (i++ < num_cmd)
	{
		temp = create_command_struct(temp, &tokens[j]);
		while (tokens[j] && !is_seperator(tokens[j]))
			j++;
		temp->nexus = tokens[j];
	}
	return (ret);
}

t_command   *parse(char *in)
{
	char	**tokens;
	int		num_cmd;

	tokens = ft_split(in, ' ');
	if (!tokens)
		return (NULL);
	num_cmd = number_of_cmd(tokens);
	return (make_command_list(num_cmd, tokens));
}

int main(void)
{
	char text[] = "this is a test < second com";
	t_command *list = parse(text);
	while (list->next)
	{
		if (list->cmd)
			printf("%s\n", list->cmd);
		printf("%d\n", list->arg_num);
		list = list->next;
	}
	return 0;
}