/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/06 16:58:24 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

void	simple_exec(t_bigshell *data) // needs to be a child bc execve will kill the process otherwise
{
	char	**paths;
	char	*correct_path;
	
	//if ((data->id = fork()) == -1)
	//	fatal_error(data, 1);
	//if (data->id == 0)
	//{
		printf("1\n");
		if (data->commands[0]->input || data->commands[0]->output)
		{
			//printf("a\n");
			redir(data->commands[0], data);
		}
		//builtin_exec(data, 0);
		printf("2\n");
		paths = find_and_split_path(data->env);
		printf("paths: %s\n", paths[1]);
		correct_path = check_if_correct_path(paths, data, data->commands[0]->cmd->str, 0);
		printf("correct path: %s\n", correct_path);
		execve(correct_path, &data->commands[0]->cmd->str, data->env);
		//protect execve
	//}
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
	//printf("what\n");
	output->str = "example";
	//printf("what\n");
	output->type = (enum type) PATH;
	//printf("what\n");
	cmd->str = "cat";
	//printf("what\n");
	cmd->type = (enum type) CMD;
	//printf("what\n");
	//arg->str = "ungüento";
	//printf("what\n");
	

	command->input = input;
	command->output = output;
	//printf("lol\n");
	command->cmd = cmd;
	//printf("lol\n");
	//command->args[0] = arg;
	//printf("lol\n");
	data.commands = &command;
	//printf("lol\n");

	//printf("hello?\n");
	simple_exec(&data);
	return (0);
}
