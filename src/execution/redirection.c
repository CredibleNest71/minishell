/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/07 10:47:09 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

//PUT CORRECT ERROR HANDLING HERE
void	store_restore_fds(t_bigshell *data, int mode)
{
	if (mode == 1)
	{
		data->std_in = dup(0);
		if (data->std_in == -1)
		{
			CRITICAL_FAILURE(data, "dup_stdin dup fail");
		}
		data->std_out = dup(1);
		if (data->std_out == -1)
		{
			CRITICAL_FAILURE(data, "dup_stdout dup fail");
		}
	}
	else if (mode == 2)
	{
		if ((dup2(data->std_in, 0)) == -1)
			CRITICAL_FAILURE(data, "dup_stdin dup2 fail");
		if ((dup2(data->std_out, 1)) == -1)
			CRITICAL_FAILURE(data, "dup_stdout dup2 fail");
		if (close(data->std_in) == - 1 || close(data->std_out) == -1)
		 	CRITICAL_FAILURE(data, "close std_in/std_out fail");
		data->std_in = -1;
		data->std_out = -1;
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
		
// fix to do: needs to be able to switch stdin&stdout multiple times (ex. cat <input >output <input2 >output3 >output4)
int	redir(t_command *command, t_bigshell *data)
{
	t_token		*in;
	t_token		*out;
	//t_command	*cmd;
	
	in = command->input;
	out = command->output;
	//cmd = data->commands;
	if (in)
	{
		if (!command->cmd && data->heredoc) //!data->commands->cmd && !data->commands->next //deleted && !command->next 6.5
			return (EXIT_FAILURE);
		else
		{
			while (in)
			{
				if (!in->next && in->type == (enum type)HEREDOC && command->cmd) // && cmd->cmd not sure why I added this //prob smt to do with pipes.
				{
					if (check_file(data, command->tmpfile, 0) != 0)
						return (EXIT_FAILURE);
					data->fd_in = open(command->tmpfile, O_RDONLY);
				}
				else if (in->type != (enum type)HEREDOC)
				{
					if (check_file(data, in->str, 0) != 0)
						return (EXIT_FAILURE);
					data->fd_in = open(in->str, O_RDONLY);
				}
				if (!in->next)
					break ;
				else
				{
					if (data->fd_in != -1 && close(data->fd_in) == -1)
						return (redir_error(data, 1, "redir.c:110 close failed"), EXIT_FAILURE);
					in = in->next;
					//cmd = cmd->next;
				}
			}
			if (data->fd_in == -1)
				return(redir_error(data, 1, "redir.c: fd_in: open failed"), EXIT_FAILURE);
			if (dup2(data->fd_in, 0) == -1)
				return(redir_error(data, 1, "redir.c: fd_in: dup2 failed"), EXIT_FAILURE);
		}
	}
	if (out)
	{
		while (out)
		{
			if (out->type == (enum type)APP)
				data->fd_out = open(out->str, O_CREAT | O_APPEND | O_WRONLY, 00644);
			else
				data->fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
			if (check_file(data, out->str, 1) != 0)
				return (EXIT_FAILURE);
			if (data->fd_out == -1)
				return(update_exit_stat(data, 1), ft_putstr_fd("minishell: No such file or directory\n", 2), EXIT_FAILURE); //printf("minishell: %s: No such file or directory\n", out->str)
			if (!out->next)
				break ;
			if (out->next)
			{
				if (data->fd_out != -1 && close(data->fd_out) == -1)
					return (redir_error(data, 1, "redir.c:137 close failed"), EXIT_FAILURE);
				out = out->next;
			}
		}
		// if (data->fd_out == -1) //tf is this for?
		// {
		// 	redir_error(data, 1, "fd_out: dup2 failed1");
		// 	return (EXIT_FAILURE);
		// }
		if ((dup2(data->fd_out, 1)) == -1)
			return(redir_error(data, 1, "fd_out: dup2 failed2"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

//1 cmd can have multiple input&output redirections, 
//in which case the last <input & >output in the cmd
//string should be used in dup2