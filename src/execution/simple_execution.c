/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/07 18:42:53 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	simple_exec(t_bigshell *data) // needs to be a child bc execve will kill the process otherwise
{
	char	**paths;
	char	*correct_path;
	
	printf("hello2\n");
	if (data->commands[0]->input || data->commands[0]->output)
		redir(data->commands[0], data);
	printf("hello2.1\n");
	builtin_check_exec(data, data->commands[0]->cmd->str, 0);
	printf("lol\n");
	paths = find_and_split_path(data->env);
	if (!paths)
		printf("find&split failed"); //shit has been allocated
	correct_path = check_if_correct_path(paths, data, data->commands[0]->cmd->str);
	if (!correct_path)
		printf("correct path failed\n"); // do smt probably
	execve(correct_path, &data->commands[0]->cmd->str, data->env);
	printf("hihi\n");
	//protect execve
}

int	main(int argc, char **argv, char **env)
{
	int j;
	t_bigshell	data;
	t_command	*command = (t_command *) malloc (sizeof(t_command));
	//t_token 	*input = (t_token *) malloc (sizeof(t_token));
	t_token 	*output = (t_token *) malloc (sizeof(t_token));
	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
	t_token 	*arg = (t_token *) malloc (sizeof(t_token));
	t_token 	*arg2 = (t_token *) malloc (sizeof(t_token));

	//input->str = "motest";
	//input->type = (enum type) PATH;
	//printf("what\n");
	output->str = "example";
	//printf("what\n");
	output->type = (enum type) PATH;
	//printf("what\n");
	cmd->str = "echo";
	//printf("what\n");
	cmd->type = (enum type) CMD;
	//printf("what\n");
	arg->str = "ungüento";
	//printf("what\n");
	arg2->str = NULL;
	

	command->args = (t_token **)malloc(sizeof(t_token *) * 2);
	//command->input = input;
	command->output = output;
	//printf("lol\n");
	command->cmd = cmd;
	//printf("lol\n");
	command->args[0] = arg;
	command->args[1] = arg2;
	//printf("lol\n");
	data.commands = &command;
	//printf("lol\n");
	
	data.built_ins = malloc(sizeof(char *) * 7);
	data.built_ins = built_in_list(&data);
	data.env = env;

	int e = 0;
	int	k = 0;
	while (e < 7)
	{
		printf("%s %d\n", data.built_ins[e], k);
		e++;
		k++;
	}

	//printf("hello?\n");
	if (argc && argv)
		j = 2;
	store_restore_fds(1);
	data.id = fork();
	if (data.id == -1)
		fatal_error(&data, 1);
	else if (data.id == 0)
	{
		simple_exec(&data);
	}
	return (0);
}
