/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/07 11:58:21 by ischmutz         ###   ########.fr       */
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

void	redir(t_command *cmd_struct, t_bigshell *main_struct)
{
	int	fd_in;
	int	fd_out;
	
	if (cmd_struct->input) // redirecting input "<"
	{
		check_file(cmd_struct->input->str, 0); //fix exit
		fd_in = open(cmd_struct->input->str, O_RDONLY);
		if (fd_in == -1)
		{
			main_struct->exit_stat = 1;
			printf("fd_in open fail");
			// main_struct->exit_stat = 
		}
			//printf error & store exit code & new prompt probably (dont exit minishell)
		if ((dup2(fd_in, 0)) == -1)
		{
			main_struct->exit_stat = 1;
			printf("fd_in dup2 fail\n");
		}
			//print error, store exit code n new prompt
	}
	if (cmd_struct->output) // redirecting output ">"
	{
		fd_out = open(cmd_struct->output->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		if (fd_out == -1)
			printf("fd_out open fail\n");
			//printf error & exit probably
		check_file(cmd_struct->output->str, 1);
		if ((dup2(fd_out, 1)) == -1)
			printf("fd_out dup2 fail\n");
			//print error, store exit code n new prompt
	}
}
