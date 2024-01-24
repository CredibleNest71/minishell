#include "../minishell.h"
#include "parse.h"


//compares string to seperating operators
int	is_seperator(char *str)
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

//returns number of commands
int	number_of_cmd(char **in)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (in[++i])
			if (is_seperator(in[i]))
				count++;
	return (count + 1);
}

//creates instance of command struct and appends it to the linked
//list if the first argument is another instance of a command struct
//returns the newly added element
t_command	*create_command_struct(t_command *prev, char **args)
{
	t_command	*ret;
	int			i;
	int			j;

	j = 0;
	i = 0;
	ret = (t_command *) malloc(sizeof(t_command));
	if (!ret)
		return (NULL);
	memset(ret, 0, sizeof(t_command));
	if (prev)
		prev->next = ret;
	ret->next = NULL;
	ret->cmd = tokenify(*args);
	ret->args = (char **) malloc (sizeof(char *) * 10);
	ret->tokens = (t_token **) malloc (sizeof(t_token *) * 10);
	if (!ret->tokens)
		return (NULL);
	memset(ret->args, 0, sizeof(char *) * 10);
	while (args[i])
	{
		if (is_seperator(args[i]))
		{
			ret->nexus = tokenify(args[i]);
			break ;
		}
		ret->args[j] = ft_strdup(args[i]);
		ret->tokens[j++] = tokenify(args[i]);
		i++;
	}
	ret->arg_num = i - 1;
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
	while (tokens[j])
	{
		if (is_seperator(tokens[j]))
			j++;
		temp = create_command_struct(temp, &tokens[j]);
		while (tokens[j] && !is_seperator(tokens[j]))
			j++;
	}
	temp = ret->next;
	free(ret);
	return (temp);
}

t_command   *parse(char *in)
{
	char	**tokens;
	int		num_cmd;

	tokens = ft_split(in, ' ');
	if (!tokens)
		return (NULL);
	num_cmd = number_of_cmd(tokens);
	printf("first: %s\n", tokens[1]);
	printf("NUM_CMD: %d\n", num_cmd);
	return (make_command_list(num_cmd, tokens));
}

void	print_command(t_command *cmd)
{
	int	i;
	char *typenames[] = {
		"CMD",
		"ARG",
		"PATH",
		"NEX",
		"DIR"
	};
	i = 0;
	printf("\n\nCOMMAND	(%d):	%s\n", cmd->arg_num, cmd->cmd->str);
	while (i++ < cmd->arg_num)
		printf(" (%s)	 %d:	%s\n", typenames[cmd->tokens[i]->type], i, cmd->args[i] );
	if (cmd->nexus)
		printf("SEP (%s): %s\n", typenames[cmd->nexus->type], cmd->nexus->str);
}

int main(int ac, char **av)
{
	char *text = av[1];
	t_command *list = parse(text);
	while (list)
	{
		print_command(list);
		list = list->next;
	}
	return 0;
}