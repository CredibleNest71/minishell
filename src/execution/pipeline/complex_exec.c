/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:43:53 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 18:43:27 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../../main/sig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static void	fork_first_cmd(t_bigshell *data, t_command *current_cmd)
{
	if (pipe(data->pipe_fd) == -1)
		critical_failure(data, "complex exec: pipe failed in first command");
	data->pipe->read = data->pipe_fd[0];
	data->pipe->write = data->pipe_fd[1];
	current_cmd->pid = fork();
	if (current_cmd->pid == -1)
		critical_failure(data, "complex exec: fork failed in first command");
	if (current_cmd->pid == 0)
		first_executor(data, current_cmd, data->pipe->write);
	if (close(data->pipe->write) == -1)
		critical_failure(data,
			"complex exec: close(1) failed in parent process");
}

static void	fork_last_cmd(t_bigshell *data, t_command *current_cmd)
{
	restore_output(data);
	current_cmd->pid = fork();
	if (current_cmd->pid == -1)
		critical_failure(data, "complex exec: fork failed in last command");
	if (current_cmd->pid == 0)
		last_executor(data, current_cmd, data->pipe->read);
	if (close(data->pipe->read) == -1)
		critical_failure(data,
			"complex exec: close(0) failed in parent process");
}

void	complex_exec2(t_bigshell *data, t_command *current_cmd)
{
	if (current_cmd == data->commands)
		fork_first_cmd(data, current_cmd);
	else
	{
		if (pipe(data->pipe_fd2) == -1)
			critical_failure(data,
				"complex exec: pipe 2 failed in middle command");
		data->pipe->write = data->pipe_fd2[1];
		current_cmd->pid = fork();
		if (current_cmd->pid == -1)
			critical_failure(data,
				"complex exec: fork failed in middle command");
		if (current_cmd->pid == 0)
			middle_executor(data, current_cmd,
				data->pipe->write, data->pipe->read);
		if (close(data->pipe->write) == -1 || close(data->pipe->read) == -1)
			critical_failure(data,
				"complex exec: close(1) failed in parent process");
		data->pipe->read = data->pipe_fd2[0];
	}
}

void	complex_exec(t_bigshell *data)
{
	t_command	*current_cmd;

	set_signals(0);
	current_cmd = data->commands;
	while (current_cmd->next)
	{
		if (g_sig == SIGINT)
			critical_failure(data, "complex exec: SIGINT received");
		complex_exec2(data, current_cmd);
		current_cmd = current_cmd->next;
	}
	if (!current_cmd->next)
	{
		if (g_sig == SIGINT)
			critical_failure(data, "complex exec: SIGINT received");
		fork_last_cmd(data, current_cmd);
	}
	wait_for_children(data);
}
