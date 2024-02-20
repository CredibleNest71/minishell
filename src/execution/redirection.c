/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/13 12:45:55 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	store_restore_fds(int mode)
{
	int	dup_stdin;
	int	dup_stdout;
	
	dup_stdin = 0;
	dup_stdout = 0;
	if (mode == 1)
	{
		if ((dup_stdin = dup(0)) == -1)
			printf("dup_stdin dup fail");
			//print error, store exit code n new prompt
		if ((dup_stdout = dup(1)) == -1)
			printf("dup_stdout dup fail");
			//print error, store exit code n new prompt
	}
	else if (mode == 2)
	{
		if ((dup2(dup_stdin, 0)) == -1)
			exit(1);
			//print error, exit code n new prompt
		if ((dup2(dup_stdout, 1)) == -1)
			exit(1);
			//print error, exit code n new prompt
	}
}

void	check_file(const char *file, int mode)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1 && mode == 0)
		printf("no such file or directory (0): %s\n", file); //check later with mo about file beig void* && pronbably exit as well
	else if (permission == -1 && mode == 1)
		return ;
	if (mode == 0)
	{
		if (access(file, R_OK) == -1)
			printf("permission denied (0): %s\n", file); //exit (make function)
	}
	else if (mode == 1)
	{
		if (access(file, W_OK) == -1)
			printf("permission denied (1): %s\n", file); //exit (make function)
	}
}

void	redir(t_command *command, t_bigshell *data) // fix to do: needs to be able to switch stdin&stdout multiple times (ex. cat <input >output <input2 >output3 >output4)
{
	int	fd_in;
	int	fd_out;
	
	if (command->input) // redirecting input "<"
	{
		check_file(command->input->str, 0); //fix exit
		fd_in = open(command->input->str, O_RDONLY);
		if (fd_in == -1)
		{
			data->exit_stat = 1;
			printf("fd_in open fail");
			// data->exit_stat = 
		}
			//printf error & store exit code & new prompt probably (dont exit minishell)
		if ((dup2(fd_in, 0)) == -1)
		{
			data->exit_stat = 1;
			printf("fd_in dup2 fail\n");
		}
			//print error, store exit code n new prompt
	}
	if (command->output) // redirecting output ">"
	{
		fd_out = open(command->output->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		if (fd_out == -1)
			printf("fd_out open fail\n");
			//printf error & exit probably
		check_file(command->output->str, 1);
		if ((dup2(fd_out, 1)) == -1)
			printf("fd_out dup2 fail\n");
			//print error, store exit code n new prompt
	}
}

//1 cmd can have multiple input&output redirections, 
//in which case the last <input & >output in the cmd
//string should be used in dup2