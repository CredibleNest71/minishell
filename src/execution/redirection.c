/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/09 11:34:15 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	restore_fork(t_bigshell *data, int mode)
{
	if (mode == 1)
	{
		if (dup2(data->pipe->write, 1) == -1)
			CRITICAL_FAILURE(data, "restoring pipe fds: dup2 write fail");
	}
	else if (mode == 2)
	{
		if(dup2(data->pipe->read, 0) == -1)
			CRITICAL_FAILURE(data, "restoring pipe fds: dup2 read fail");
		if (dup2(data->pipe->write, 1) == -1)
			CRITICAL_FAILURE(data, "restoring pipe fds: dup2 write fail");
	}
	else if (mode == 3)
	{
		if(dup2(data->pipe->read, 0) == -1)
			CRITICAL_FAILURE(data, "restoring pipe fds: dup2 read fail");
	}
}

//PUT CORRECT ERROR HANDLING HERE
void	store_restore_fds(t_bigshell *data, int mode)
{
	if (mode == 1)
	{
		data->std_in = dup(0);
		if (data->std_in == -1)
		{
			//printf("que\n"); //debugging printf
			CRITICAL_FAILURE(data, "dup_stdin dup fail");
		}
		data->std_out = dup(1);
		if (data->std_out == -1)
		{
			//printf("mierda\n"); //debugging printf
			CRITICAL_FAILURE(data, "dup_stdout dup fail");
		}
	}
	else if (mode == 2)
	{
		if ((dup2(data->std_in, 0)) == -1) //|| close(data->std_in) == -1 || close(data->std_out) == -1
			CRITICAL_FAILURE(data, "dup_stdin dup2 fail");
		if ((dup2(data->std_out, 1)) == -1) // || close(data->std_in) == -1 || close(data->std_out) == -1
			CRITICAL_FAILURE(data, "dup_stdout dup2 fail");
	}
}

/* printf("minishell: %s: No such file or directory\n", file); //check later with mo about file beig void* && probably exit as well
data->exit_stat = 1; //$? --> 1: command not found */
int	check_file(t_bigshell *data, const char *file, int mode)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1 && mode == 0)
	{
		redir_error(data, 1, "minishell: No such file or directory");
		return (EXIT_FAILURE);
	}
	else if (permission == -1 && mode == 1)
		return (EXIT_SUCCESS);
	if (mode == 0)
	{
		if (access(file, R_OK) == -1)
		{
			redir_error(data, 1, "minishell: Permission denied");
			return (EXIT_FAILURE);
		}
	}
	else if (mode == 1)
	{
		if (access(file, W_OK) == -1)
		{
			redir_error(data, 1, "minishell: Permission denied");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

//this was before line 108
			/* if (!in->next)
			{
				if (check_file(data, in->str, 0) != 0)
					return (EXIT_FAILURE);
				data->fd_in = open(in->str, O_RDONLY);
			} */
//this was right after (this part was modified)
			/* while (in->next)
			{
				if (check_file(data, in->str, 0) != 0)
					return (EXIT_FAILURE);
				data->fd_in = open(in->str, O_RDONLY);
				in = in->next;
			} */
//this was line 130 before
		/* if (!out->next)
			data->fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644); */
			
// fix to do: needs to be able to switch stdin&stdout multiple times (ex. cat <input >output <input2 >output3 >output4)
int	redir(t_command *command, t_bigshell *data)
{
	t_token	*in;
	t_token	*out;
	
	in = command->input;
	out = command->output;
	if (in)
	{
		if (data->heredoc)
		{
			if (check_file(data, "tmpfile.txt", 0) != 0)
				return (EXIT_FAILURE);
		}
		else
		{
			while (in)
			{
				if (check_file(data, in->str, 0) != 0)
					return (EXIT_FAILURE);
				data->fd_in = open(in->str, O_RDONLY);
				if (!in->next)
					break ;
				else
					in = in->next;
			}
			if (data->fd_in == -1)
			{
				redir_error(data, 1, "fd_in: open failed");
				return (EXIT_FAILURE);
			}
			if ((dup2(data->fd_in, 0)) == -1)
				CRITICAL_FAILURE(data, "fd_in dup2 fail");
		}
	}
	if (out)
	{
		while (out)
		{
			data->fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
			if (data->fd_out == -1)
				CRITICAL_FAILURE(data, "redirection: open failed");
			if (!out->next)
				break ;
			if (out->next)
				out = out->next;
		}
		if (data->fd_out == -1)
			CRITICAL_FAILURE(data, "redirection: open failed");
		if (check_file(data, out->str, 1) != 0)
			return (EXIT_FAILURE);
		if ((dup2(data->fd_out, 1)) == -1)
			CRITICAL_FAILURE(data, "fd_out dup2 fail");
	}
	return (EXIT_SUCCESS);
}

//1 cmd can have multiple input&output redirections, 
//in which case the last <input & >output in the cmd
//string should be used in dup2