/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/21 19:44:56 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "../../minishell.h"
#include <stdio.h>
#include <strings.h>

// needs to be a child bc execve will kill the process otherwise
//we 1st check if redir is needed. <input & <<heredoc are both stored in cmd->input
//therefore if im coming from heredoc it'll enter redir. If <<heredoc is the final
//file then ill try to access it. have to make tmpfile.txt accesible to redir()
//overwrite input->str? (stupid? probably) make new struct member char *heredoc_file?

/* void	check_input_file(t_bigshell *data, char *file)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1)
		simple_error(data, 1); //wrong file permission whats exit code?
	permission = access(file, R_OK);
	if (permission == -1)
		simple_error(data, 1);
} */

void	simple_exec(t_bigshell *data)
{
	char	**paths;
	char	*correct_path;
	
	paths = NULL;
	correct_path = NULL;
	convert_env(data); //check this function env struct has changed
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		//printf("find&split failed\n"); //shit has been allocated
	correct_path = check_if_correct_path(paths, data, data->commands->cmd->str);
	if (!correct_path)
		//printf("minishell: command %s not found\n", data->commands->cmd->str);
	execve(correct_path, data->commands->args_exec, data->mod_env);
	////printf("minishell: command %s not found\n", data->commands->cmd->str);
	free(correct_path);
	//free paths & args_exec
	////printf("execve failed\n");
	//protect execve
}

/* void print_env_list(t_bigshell *data)
{
    t_env *current = data->env;
    while (current != NULL)
    {
        //printf("%s\n", current->str);
        current = current->next;
    }
} */
// t_sig	g_sig;

// int	main(int argc, char **argv, char **env)
// {
// 	t_bigshell	data;
// 	//data = (t_bigshell *)malloc(sizeof(t_bigshell));
// // 	t_command	*command = (t_command *) malloc (sizeof(t_command));
// // 	//t_command	*command2 = (t_command *) malloc (sizeof(t_command));
// // 	//t_token 	*input = (t_token *) malloc (sizeof(t_token));
// // 	//t_token 	*output = (t_token *) malloc (sizeof(t_token));
// // 	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
// // 	//t_token 	*cmd2 = (t_token *) malloc (sizeof(t_token));
// // 	t_token 	*arg = (t_token *) malloc (sizeof(t_token));
// // 	t_token 	*arg2 = (t_token *) malloc (sizeof(t_token));
// // 	//t_token 	*arg3 = (t_token *) malloc (sizeof(t_token));

// // 	//input->str = "motest";
// // 	//input->type = (enum type) PATH;
// // 	////printf("what\n");
// // 	//output->str = "example";
// // 	////printf("what\n");
// // 	//output->type = (enum type) PATH;
// // 	////printf("what\n");
// // 	cmd->str = "unset";
// // 	//cmd2->str = "unset";
// // 	////printf("what\n");
// // 	cmd->type = (enum type) CMD;
// // 	////printf("what\n");
// // 	arg->str = "Amy=var";
// // 	////printf("what\n");
// // 	arg2->str = "Zmyvar=0";
// // 	//arg3->str = "Zmyvar=0";
// // 	arg->next = arg2;
// // 	arg2->next = NULL;
// // 	//arg3->next = NULL;
	

// // 	command->args = arg;
// // 	//command2->args = arg3;
// // 	//command->input = input;
// // 	//command->output = output;n
// // 	////printf("lol\n");
// // 	command->cmd = cmd;
// // 	//command2->cmd = cmd2;
// // 	////printf("lol\n");
// // 	//command->args[0] = arg;
// // 	//command->args[1] = arg2;
// // 	//command->args = NULL;
// // 	////printf("lol\n");
// // 	command->arg_num = 2;
// // 	//command->next = command2;
// // 	data.commands = command;
// // 	////printf("lol\n");
	
// // 	data.reference_i = 0;
// // 	data.s_env = NULL;

// //     // Store environment strings in the linked list
//      //store_env(&data, env);
// // 	ft_export(&data);
// // 	//data.commands->args = arg2;
// // 	////printf("%s\n", data.commands->args->str);
// // 	//print_env(data.s_env);
// // 	//free_env(&data);
// // 	//ft_unset(&data);
// // 	//print_env(data.env);
// // 	//make_copy(&data);
// // 	////printf("%d\n", data.reference_i);

// //     // Print the linked list
// //     //print_env_list(&data);
// // 	//convert_env(&data);
// // 	/* int e = -1;
// // 	while (data.mod_env[++e])
// // 	{
// // 		//printf("%s\n", data.mod_env[e]);
// // 	} */
	
// //  	if (!data.built_ins)
// // 	{
// // 		//printf("malloc failed\n");
// // 	}
// // 	//data.built_ins = built_in_list(&data);
// // 	//free(data.built_ins);
// // 	//free_builtin_list(&data);
// // 	// free_builtin_list(&data);
// // 	//printf("a\n");
// // 	//proabbaly segfault bc there are uninitialized shit will be fixed with merge?
// // 	free_struct(&data);
// // 	return 0;
// // 	/* int e = 0;
// // 	while (e < 7)
// // 		//printf("%s\n", data.built_ins[e++]); */

// // 	/* int j;
// // 	if (argc && argv)
// // 		j = 2;
// // 	j = 0; */
	
// // 	//data.commands = data.commands->next;

// 	if (argc && argv) 
// 		//printf("");
// // 	/* store_restore_fds(1);
// // 	simple_exec(&data); */
// // /* 	data.id = fork();
// // 	if (data.id == -1)
// // 	 	CRITICAL_FAILURE(&data);
// // 	else if (data.id == 0)
// // 	{
// // 		simple_exec(&data);
// // 	}
// // 	return (0); */
// 	bzero(&data, sizeof(t_bigshell));
//  	data.og_env = env;
// 	store_env(&data, env);
//  	//data.built_ins = (char **)malloc(sizeof(char *) * 8); //7 elements plus NULL
//  	//built_in_list(&data);
// 	char *lineread;
// 	lineread = NULL;
// 	/* lineread = readline("tinyshell: ");
// 	data.commands = parse(lineread, &data);
// 	data.commands->arg_num = 0;
// 	//printf("%d\n", data.commands->arg_num);
// 	ft_cd(&data); */
// 	while (1)
// 	{
// 		lineread = readline("tinyshell: ");
// 		add_history(lineread);
// 		data.commands = parse(lineread, &data);
// 		if (!data.commands)
// 			continue ;
// 		print_cmds(data.commands, &data);
// 		store_restore_fds(&data, 1);
// 		if (heredoc_finder(&data) == 0)
// 			ft_heredoc(&data);
// 		if (data.commands->input || data.commands->output)
// 		{
// 			if (redir(data.commands, &data) != 0)
// 			{
// 				store_restore_fds(&data, 2);
// 				continue ;
// 			}
// 		}
// 		if (builtin_allrounder(&data) == 0)
// 		{
// 			store_restore_fds(&data, 2);
// 			continue ;
// 		}
// 		//print_cmds(data.commands);
// 		if (data.num_cmd == 1)
// 		{
// 			data.id = fork();
// 			if (data.id == -1)
// 				CRITICAL_FAILURE(&data, "1: fork failed");
// 			if (data.id == 0)
// 				simple_exec(&data);
// 			wait(NULL);
// 		}
// 		/* else if (data.num_cmd > 1)
// 		{
// 			int i = 0;
// 			while (i < data.num_cmd)
// 			{
// 				complex_exec(&data, i);
// 			}
// 		} */
// 	//int i = 0;
// 		/* else if (data.num_cmd > 1)
// 		{
// 			while (i < (data.num_cmd - 1))
// 			{
// 				if (pipe(data.pipe_fd) == -1)
// 				{
// 					//printf("pipe failed\n");
// 					CRITICAL_FAILURE(data);
// 				}
// 				int j = i;
// 				while (i < data.num_cmd)
// 				{}
// 				i++;
// 				if (i == data.num_cmd)
// 				{
// 					close(data.pipe_fd[1]);
// 					close(data.pipe_fd[0]);
// 				}
// 			}
// 		} */
// 		store_restore_fds(&data, 2);
// 	}
// }
