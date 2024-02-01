/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/01 11:34:05 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_restore_fds(int mode)
{
	int	dup_stdin;
	int	dup_stdout;
	
	if (mode == 1)
	{
		if ((dup_stdin = dup(0)) == -1)
			//print error, store exit code n new prompt
		if ((dup_stdout = dup(1)) == -1)
			//print error, store exit code n new prompt
	}
	else if (mode == 2)
	{
		if ((dup2(dup_stdin, 0)) == -1)
			//print error, exit code n new prompt
		if ((dup2(dup_stdout, 1)) == -1)
			//print error, exit code n new prompt
	}
}

int	check_file(t_token *file, int mode)
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

void	redir(t_command *cmd_struct, t_bigshell **main_struct)
{
	int	fd_in;
	int	fd_out;
	
	if (cmd_struct->input) // redirecting input "<"
	{
		check_file(cmd_struct->input, 0); //fix exit
		fd_in = open(cmd_struct->input, O_RDONLY);
		if (fd_in == -1)
		{
			main_struct->
		}
			//printf error & store exit code & new prompt probably (dont exit minishell)
		if ((dup2(fd_in, 0)) == -1)
			//print error, store exit code n new prompt
	}
	if (cmd_struct->output) // redirecting output ">"
	{
		fd_out = open(cmd_struct->output, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		if (fd_out == -1)
			//printf error & exit probably
		check_file(cmd_struct->output, 1);
		if ((dup2(fd_out, 1)) == -1)
			//print error, store exit code n new prompt
	}
}
