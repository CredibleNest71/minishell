/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/06 14:38:35 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	simple_exec(t_bigshell *data) // needs to be a child bc execve will kill the process otherwise
{
	char	**paths;
	char	*correct_path;
	
	if ((data->id = fork()) == -1)
		fatal_error(data, 1);
	printf("searcching\n");
	if (data->id == 0)
	{
		if (data->commands[0]->input || data->commands[0]->output)
			redir(data->commands[0], data);
		//builtin_exec(data, 0);
		paths = find_and_split_path(data->env);
		correct_path = check_if_correct_path(paths, data, data->commands[0]->cmd->str, 0);
		execve(correct_path, &data->commands[0]->cmd->str, data->env);
		//protect execve
	}
}

int	main()
{
	t_bigshell	data;
	t_command	*command = (t_command *) malloc (sizeof(t_command));
	//t_token 	*input = (t_token *) malloc (sizeof(t_token));
	t_token 	*output = (t_token *) malloc (sizeof(t_token));
	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
	t_token 	*arg = (t_token *) malloc (sizeof(t_token));

	// input->str = "motest";
	// input->type = (enum type) PATH;
	output->str = "example";
	output->type = (enum type) PATH;
	cmd->str = "echo";
	cmd->type = (enum type) CMD;
	arg->str = "ungüento";
	

	//command->input = input;
	command->output = output;
	command->cmd = cmd;
	command->args[0] = arg;
	
	data.commands = &command;

	simple_exec(&data);
	return (0);
}
