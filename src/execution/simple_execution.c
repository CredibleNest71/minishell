/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/23 10:56:26 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// needs to be a child bc execve will kill the process otherwise
void	simple_exec(t_bigshell *data)
{
	char	**paths;
	char	*correct_path;
	
	if (data->commands->input || data->commands->output)
		redir(data->commands, data);
	builtin_check_exec(data, data->commands->cmd->str);
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //shit has been allocated
	correct_path = check_if_correct_path(paths, data, data->commands->cmd->str);
	if (!correct_path)
		printf("correct path failed\n"); // do smt probably
	execve(correct_path, &data->commands->cmd->str, data->mod_env);
	printf("execve failed\n");
	//protect execve
}

/* void print_env_list(t_bigshell *data)
{
    t_env *current = data->env;
    while (current != NULL)
    {
        printf("%s\n", current->str);
        current = current->next;
    }
} */

int	main(int argc, char **argv, char **env)
{
	t_bigshell	data;
	t_command	*command = (t_command *) malloc (sizeof(t_command));
	//t_token 	*input = (t_token *) malloc (sizeof(t_token));
	//t_token 	*output = (t_token *) malloc (sizeof(t_token));
	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
	t_token 	*arg = (t_token *) malloc (sizeof(t_token));
	t_token 	*arg2 = (t_token *) malloc (sizeof(t_token));
	//t_token 	*arg3 = (t_token *) malloc (sizeof(t_token));

	//input->str = "motest";
	//input->type = (enum type) PATH;
	//printf("what\n");
	//output->str = "example";
	//printf("what\n");
	//output->type = (enum type) PATH;
	//printf("what\n");
	cmd->str = "export";
	//printf("what\n");
	cmd->type = (enum type) CMD;
	//printf("what\n");
	arg->str = "amy=var";
	//printf("what\n");
	arg2->str = "Zmyvar=0";
	//arg3 = NULL;
	arg->next = arg2;
	arg2->next = NULL;
	

	command->args = arg;
	//command->input = input;
	//command->output = output;n
	//printf("lol\n");
	command->cmd = cmd;
	//printf("lol\n");
	//command->args[0] = arg;
	//command->args[1] = arg2;
	//command->args = NULL;
	//printf("lol\n");
	command->arg_num = 2;
	data.commands = command;
	//printf("lol\n");
	
	data.og_env = env;
	data.reference_i = 0;
	data.s_env = NULL;

    // Store environment strings in the linked list
    store_env(&data, env);

    // Print the linked list
    //print_env_list(&data);
	//convert_env(&data);
	/* int e = -1;
	while (data.mod_env[++e])
	{
		printf("%s\n", data.mod_env[e]);
	} */
	
	data.built_ins = (char **)malloc(sizeof(char *) * 7);
/* 	if (!data.built_ins)
	{
		printf("malloc failed\n");
		exit(1);qq
	} */
	//data.built_ins = built_in_list(&data);
	built_in_list(&data);
	/* int e = 0;
	while (e < 7)
		printf("%s\n", data.built_ins[e++]); */

	/* int j;
	if (argc && argv)
		j = 2;
	j = 0; */
	if (argc == 10 || argv[1]) 
		printf("unecessary stuff\n");
	store_restore_fds(1);
	simple_exec(&data);
/* 	data.id = fork();
	if (data.id == -1)
	 	fatal_error(&data, 1);
	else if (data.id == 0)
	{
		simple_exec(&data);
	}
	return (0); */
}
