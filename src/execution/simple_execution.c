/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/05 18:11:57 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
} */

void	simple_exec(t_bigshell *data)
{
	char	**paths;
	char	*correct_path;
	
	if (data->commands[0]->input || data->commands[0]->output)
		redir(data->commands[0], data);
	builtin_exec(data, 0);
	paths = find_and_split_path(data->env);
	correct_path = check_if_correct_path(paths, data, data->commands[0]->cmd->str, 0);
	execve(correct_path, &data->commands[0]->cmd->str, data->env);
	//protect execve
}


int	main()
{
	t_bigshell	data;
	t_command	*command = (t_command *) malloc (sizeof(t_command));
	t_token 	*input = (t_token *) malloc (sizeof(t_token));
	t_token 	*output = (t_token *) malloc (sizeof(t_token));
	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
	//t_token 	*arg = (t_token *) malloc (sizeof(t_token));

	input->str = "motest";
	input->type = (enum type) PATH;
	output->str = "example";
	output->type = (enum type) PATH;
	cmd->str = "cat";
	cmd->type = (enum type) CMD;

	command->input = input;
	command->output = output;
	command->cmd = cmd;
	//command->args = 0;
	
	data.commands = &command;

	simple_exec(&data);
	return (0);
}