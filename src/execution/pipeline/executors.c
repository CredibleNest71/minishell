/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:18:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 16:05:05 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../../main/sig.h"

void	execute_command(t_bigshell *data, t_command *cmd)
{
	data->exec->paths = NULL;
	data->exec->path = NULL;
	if (!builtin_allrounder(data, cmd))
		exit_child(data, 0);
	close_redir_fds_in_child(data);
	convert_env(data);
	data->exec->paths = find_and_split_path(data->mod_env);
	if (!data->exec->paths)
		exit_child(data, 1);
	data->exec->path = check_if_correct_path(data->exec->paths,
			data, cmd->cmd->str);
	if (!data->exec->path)
		error_exit(data, 127, "command not found");
	execve(data->exec->path, cmd->args_exec, data->mod_env);
	if (data->exec->path[0] == '/' || data->exec->path[0] == '.')
		error_exit(data, 127, "command not found");
	exit_child(data, 126);
}

void	first_executor(t_bigshell *data, t_command *cmd, int out_fd)
{
	data->exec->paths = NULL;
	data->exec->path = NULL;
	set_signals(3);
	if (cmd->input || cmd->output)
	{
		close_redir_fds_in_child(data);
		if (redir(cmd, data))
			exit_child(data, 1);
	}
	if (!cmd->output)
	{
		if (dup2(out_fd, 1) == -1 || close(data->pipe->read) == -1 || \
			close(data->pipe->write) == -1)
			critical_failure(data, "complex exec: first executor: dup2 failed");
	}
	execute_command(data, cmd);
}

void	last_executor(t_bigshell *data, t_command *cmd, int in_fd)
{
	set_signals(3);
	data->exec->paths = NULL;
	data->exec->path = NULL;
	if (cmd->input || cmd->output)
	{
		close_redir_fds_in_child(data);
		if (redir(cmd, data))
		{
			close(data->pipe_fd[0]);	
			exit_child(data, 1);
		}
	}
	if (!cmd->input)
	{
		if (dup2(in_fd, 0) == -1 || close(data->pipe->read))
			critical_failure(data, "complex exec: last executor: dup2 failed");
	}
	//  if (data->pipe_fd[0])
	//  	close(data->pipe_fd2[0]);
	//  if (data->pipe_fd[1])
	//  	close(data->pipe_fd2[1]);
	//close(in_fd);
	execute_command(data, cmd);
}

void	middle_executor(t_bigshell *data, t_command *cmd, int out_fd, int in_fd)
{
	data->exec->paths = NULL;
	data->exec->path = NULL;
	set_signals(3);
	if (cmd->input || cmd->output)
	{
		close_redir_fds_in_child(data);
		if (redir(cmd, data))
			exit_child(data, 1);
	}
	if (!cmd->input)
	{
		if (dup2(in_fd, 0) == -1 || close(in_fd) == -1)
			critical_failure(data, "complex exec: middle executor: \
			dup2 failed (in_fd)");
	}
	if (!cmd->output)
	{
		if (dup2(out_fd, 1) == -1 || close(out_fd) == -1)
			critical_failure(data, "complex exec: middle executor: \
			dup2 failed (out_fd)");
	}
	//this should be closed if redir didnt fail
	// close(out_fd);
	// close(in_fd);
	if (close(data->pipe_fd[1]) == -1)
		critical_failure(data, "closing pipe");
	execute_command(data, cmd);
}
