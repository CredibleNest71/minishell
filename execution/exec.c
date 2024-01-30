/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:05:40 by ischmutz          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:30 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

// use 0 for success, as for other shit check bash exit codes

//if redirection == NULL
//use stdin, stdout & stderr

/* void	wait_for_offspring(//struct)
{
	waitpid(//struct->id, &data->exitstatus, 0);
	waitpid(//struct->id2, &data->exitstatus, 0);
	if (WIFEXITED(//struct->exitstatus))
		//struct->exitstatus = WEXITSTATUS(//struct->exitstatus);
} */

void	builtin_exec(/*cmd arg*/)
{
	// check if cmd is empty
	// check if cmd is one of the built-ins
		// store cmd names with  
}

int	check_file(void	*file, int mode)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1 && mode == 0)
		printf("no such file or directory: %s\n", file); //check later with mo about file beig void* && pronbably exit as well
	if (mode == 0)
	{
		permission = access(file, R_OK);
		printf("permission denied: %s\n", file); //exit (make function)
	}
	else if (mode == 1)
	{
		permission = access(file, W_OK);
		if (permission == -1)
			printf("permission denied: %s\n", file); //exit (make function)
	}
	return (0);
}

void	redir(t_command *cmd_struct)
{
	int	fd_in;
	int	fd_out;
	
	if (cmd_struct->input) // redirecting input "<"
	{
		check_file(cmd_struct->input, 0); //fix exit
		fd_in = open(cmd_struct->input, O_RDONLY);
		if (fd_in == -1)
			//printf error & exit probably	
	}
	if (cmd_struct->output) // redirecting output ">"
	{
		fd_out = open(cmd_struct->output, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		if (fd_out == -1)
			//printf error & exit probably
		check_file(cmd_struct->output, 1);
	}
}

void	exec(t_command *cmd_table) //do I want to modify the struct?
{
	int	pid;
	int	i;

	i = 0;
	if (redirection == yes)//check for redirection
		//dup2 the shit outta this
		redir();
	if (cmd_table->cmd[i] && !(cmd_table->cmd[i + 1])) //check if there's only one command or check that no pipes exist
		//builtin_exec(cmd arg);
	while (i < cmd_table->arg_num)
	{
		pid = fork();
		if (pid == 0) //child
			//execute cmd;
			//remember to handle error (send correct exit code)
		if (pid == -1) //fork failed (check errno?)
			//handle error (send correct exit code)
		//probably close fds;
		//wait_for_offspring(struct);
	}
}