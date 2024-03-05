/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/05 15:02:31 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "../../minishell.h"

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

int	main(/*int argc, char **argv, char **env*/)
{
	t_bigshell	data;
// 	t_command	*command = (t_command *) malloc (sizeof(t_command));
// 	//t_command	*command2 = (t_command *) malloc (sizeof(t_command));
// 	//t_token 	*input = (t_token *) malloc (sizeof(t_token));
// 	//t_token 	*output = (t_token *) malloc (sizeof(t_token));
// 	t_token 	*cmd = (t_token *) malloc (sizeof(t_token));
// 	//t_token 	*cmd2 = (t_token *) malloc (sizeof(t_token));
// 	t_token 	*arg = (t_token *) malloc (sizeof(t_token));
// 	t_token 	*arg2 = (t_token *) malloc (sizeof(t_token));
// 	//t_token 	*arg3 = (t_token *) malloc (sizeof(t_token));

// 	//input->str = "motest";
// 	//input->type = (enum type) PATH;
// 	//printf("what\n");
// 	//output->str = "example";
// 	//printf("what\n");
// 	//output->type = (enum type) PATH;
// 	//printf("what\n");
// 	cmd->str = "unset";
// 	//cmd2->str = "unset";
// 	//printf("what\n");
// 	cmd->type = (enum type) CMD;
// 	//printf("what\n");
// 	arg->str = "Amy=var";
// 	//printf("what\n");
// 	arg2->str = "Zmyvar=0";
// 	//arg3->str = "Zmyvar=0";
// 	arg->next = arg2;
// 	arg2->next = NULL;
// 	//arg3->next = NULL;
	

// 	command->args = arg;
// 	//command2->args = arg3;
// 	//command->input = input;
// 	//command->output = output;n
// 	//printf("lol\n");
// 	command->cmd = cmd;
// 	//command2->cmd = cmd2;
// 	//printf("lol\n");
// 	//command->args[0] = arg;
// 	//command->args[1] = arg2;
// 	//command->args = NULL;
// 	//printf("lol\n");
// 	command->arg_num = 2;
// 	//command->next = command2;
// 	data.commands = command;
// 	//printf("lol\n");
	
// 	data.og_env = env;
// 	data.reference_i = 0;
// 	data.s_env = NULL;

//     // Store environment strings in the linked list
//     store_env(&data, env);
// 	ft_export(&data);
// 	//data.commands->args = arg2;
// 	//printf("%s\n", data.commands->args->str);
// 	//print_env(data.s_env);
// 	//free_env(&data);
// 	//ft_unset(&data);
// 	//print_env(data.env);
// 	//make_copy(&data);
// 	//printf("%d\n", data.reference_i);

//     // Print the linked list
//     //print_env_list(&data);
// 	//convert_env(&data);
// 	/* int e = -1;
// 	while (data.mod_env[++e])
// 	{
// 		printf("%s\n", data.mod_env[e]);
// 	} */
	
// 	data.built_ins = (char **)malloc(sizeof(char *) * 8); //7 elements plus NULL
//  	if (!data.built_ins)
// 	{
// 		printf("malloc failed\n");
// 	}
// 	//data.built_ins = built_in_list(&data);
// 	built_in_list(&data);
// 	//free(data.built_ins);
// 	//free_builtin_list(&data);
// 	// free_builtin_list(&data);
// 	printf("a\n");
// 	//proabbaly segfault bc there are uninitialized shit will be fixed with merge?
// 	free_struct(&data);
// 	return 0;
// 	/* int e = 0;
// 	while (e < 7)
// 		printf("%s\n", data.built_ins[e++]); */

// 	/* int j;
// 	if (argc && argv)
// 		j = 2;
// 	j = 0; */
	
// 	//data.commands = data.commands->next;

// 	if (argc && argv) 
// 		printf("unecessary stuff\n");
// 	/* store_restore_fds(1);
// 	simple_exec(&data); */
// /* 	data.id = fork();
// 	if (data.id == -1)
// 	 	fatal_error(&data, 1);
// 	else if (data.id == 0)
// 	{
// 		simple_exec(&data);
// 	}
// 	return (0); */
	char *lineread;
	lineread = readline("tinyshell: ");
	data.commands = parse(lineread, &data);
	//print_cmds(data.commands);
	ft_heredoc(&data);
}
