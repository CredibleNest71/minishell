/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/07 17:42:13 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//PUT CORRECT ERROR HANDLING HERE
void	store_restore_fds(t_bigshell *data, int mode) //REMOVE printfs
{
	/* int	dup_stdin;
	int	dup_stdout;
	
	dup_stdin = 0;
	dup_stdout = 0; */
	if (mode == 1)
	{
		if ((data->std_in = dup(0)) == -1)
			printf("dup_stdin dup fail");
			//print error, store exit code n new prompt
		if ((data->std_out = dup(1)) == -1)
			printf("dup_stdout dup fail");
			//print error, store exit code n new prompt
	}
	else if (mode == 2)
	{
		if ((dup2(data->std_in, 0)) == -1)
			printf("dup_stdin dup2 fail");
			//print error, exit code n new prompt
		if ((dup2(data->std_out, 1)) == -1)
			printf("dup_stdout dup2 fail");
			//print error, exit code n new prompt
	}
}

void	check_file(t_bigshell *data, const char *file, int mode)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1 && mode == 0)
	{
		printf("no such file or directory (0): %s\n", file); //check later with mo about file beig void* && probably exit as well
		simple_error(data, 1);
	}
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
	int		fd_in;
	int		fd_out;
	t_token	*in;
	t_token	*out;
	
	in = command->input;
	out = command->output;
	if (in) // redirecting input "<"
	{
		if (data->heredoc)
			check_file(data, "tmpfile.txt", 0);
		else
		{
			while (in->next)
			{
				check_file(data, in->str, 0); //fix exit
				fd_in = open(in->str, O_RDONLY);
				in = in->next;
			}
			if (!in->next)
			{
				check_file(data, in->str, 0); //fix exit
				fd_in = open(in->str, O_RDONLY);
			}
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
		}
			//print error, store exit code n new prompt
	}
	if (out) // redirecting output ">"
	{
		if (!out->next)
		{
			fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);	
		}
		while (out->next)
		{
			fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
			out = out->next;
		}
		fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		if (fd_out == -1)
			printf("fd_out open fail\n");
			//printf error & exit probably
		check_file(data, out->str, 1);
		if ((dup2(fd_out, 1)) == -1)
			printf("fd_out dup2 fail\n");
			//print error, store exit code n new prompt
	}
}

//1 cmd can have multiple input&output redirections, 
//in which case the last <input & >output in the cmd
//string should be used in dup2