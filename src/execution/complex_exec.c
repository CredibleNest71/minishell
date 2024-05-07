/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:43:53 by ischmutz          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/06 19:05:01 by ischmutz         ###   ########.fr       */
=======
/*   Updated: 2024/05/07 10:44:53 by a                ###   ########.fr       */
>>>>>>> refs/remotes/origin/exec
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../main/sig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

//what happens if there are multiple cmds but no pipes??? check main will it still act as if its being piped???
// I need to check for first cmd and create pipe
//then ill check for middle if encountered I overwrite stdout, otherwise I dont

void	pipe_init(t_bigshell *data)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		CRITICAL_FAILURE(data, "pipe_init: malloc fail");
	data->pipe = pipe;
}

void    restore_output(t_bigshell *data)
{
    if (dup2(data->std_out, 1) == -1)
        CRITICAL_FAILURE(data, "restoring stdout: dup2 fail");
}

void	wait_for_children(t_bigshell *data)
{
	t_command	*cmd;
	int			stat_loc;

	cmd = data->commands;
	stat_loc = get_exitcode(data);
	while (cmd)
	{
		waitpid(cmd->pid, &stat_loc, 0);
		if (WIFEXITED(stat_loc))
		{
			stat_loc = WEXITSTATUS(stat_loc);
			update_exit_stat(data, stat_loc);
		}
		if (WIFSIGNALED(stat_loc))
		{
			stat_loc = WTERMSIG(stat_loc);
			update_exit_stat(data, stat_loc);
		}
		cmd = cmd->next;
	}
}

void	first_executor(t_bigshell *data, t_command *cmd, int out_fd)
{
	data->exec->paths = NULL;
	data->exec->path = NULL;
	
	if (cmd->input || cmd->output)
	{
		close_redir_fds_in_child(data);
		if (redir(cmd, data))
			exit_child(data, 1);
	}
	if (!cmd->output)
	{
		if (dup2(out_fd, 1) == -1 || close_pipe(data, 3)) //close(data->pipe->read) == -1 || close(data->pipe->write) == -1
			CRITICAL_FAILURE(data, "complex exec: first executor: dup2 failed");
	}
	if (!builtin_allrounder(data, cmd))
		exit_child(data, 0);
	convert_env(data);
	data->exec->paths = find_and_split_path(data->mod_env);
	if (!data->exec->paths)
		exit_child(data, 1);
	data->exec->path = check_if_correct_path(data->exec->paths, data, cmd->cmd->str);
	if (!data->exec->path)
	{
<<<<<<< HEAD
		//printf("minishell: command '%s' not found\n", cmd->cmd->str);
		ft_putstr_fd("minishell: command not found\n", 2);
=======
		ft_putstr_fd("minishell: command not found\n", 2);
		//printf("minishell: command '%s' not found\n", cmd->cmd->str);
>>>>>>> refs/remotes/origin/exec
		exit_child(data, 127);
	}
	execve(data->exec->path, cmd->args_exec, data->mod_env);
	if (data->exec->path[0] == '/' || data->exec->path[0] == '.')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		//printf("minishell: command '%s' not found\n", data->exec->path);
		exit_child(data, 127);
	}
	exit_child(data, 126);
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
			exit_child(data, 1);
	}
	if (!cmd->input)
	{
		if (dup2(in_fd, 0) == -1) //|| close(data->pipe->write) == -1 || close(data->pipe->read) == -1)
			CRITICAL_FAILURE(data, "complex exec: last executor: dup2 failed");
	}
	close_read(data);
	//close(in_fd);
	if (!builtin_allrounder(data, cmd))
	 	exit_child(data, 0);
	//close_redir_fds_in_child(data);
	convert_env(data);
	data->exec->paths = find_and_split_path(data->mod_env);
	if (!data->exec->paths)
		exit_child(data, 1); //printf("find&split failed\n"); //handle correctly
	data->exec->path = check_if_correct_path(data->exec->paths, data, cmd->cmd->str);
	if (!data->exec->path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		//printf("minishell: command %s not found\n", cmd->cmd->str);
		exit_child(data, 127);
	}
	execve(data->exec->path, cmd->args_exec, data->mod_env);
	if (data->exec->path[0] == '/' || data->exec->path[0] == '.')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		//printf("minishell: command '%s' not found\n", data->exec->path);
		exit_child(data, 127);
	}
	exit_child(data, 126);

}

void	middle_executor(t_bigshell *data, t_command *cmd, int out_fd, int in_fd)
{
	data->exec->paths = NULL;
	data->exec->path = NULL;
	
	if (cmd->input || cmd->output)
	{
		close_redir_fds_in_child(data);
		if (redir(cmd, data))
			exit_child(data, 1);
	}
	if (!cmd->input)
	{
		if (dup2(in_fd, 0) == -1 || close_read(data)) // || close(data->pipe->write) == -1) cmd->prev->in_fd --> artem
			CRITICAL_FAILURE(data, "complex exec: middle executor: dup2 failed (in_fd)");
		//close(in_fd);
	}
	if (!cmd->output)
	{
		if (dup2(out_fd, 1) == -1 || close_write(data)) //close(data->pipe->read) == -1 ||
			CRITICAL_FAILURE(data, "complex exec: middle executor: dup2 failed (out_fd)");
		//close(out_fd);
	}
	//this should be closed if redir didnt fail
	// close(out_fd);
	// close(in_fd);
	if (!builtin_allrounder(data, cmd))
		exit_child(data, 0);
	//close_redir_fds_in_child(data);
	convert_env(data);
	data->exec->paths = find_and_split_path(data->mod_env);
	if (!data->exec->paths)
		exit_child(data, 1);
	data->exec->path = check_if_correct_path(data->exec->paths, data, cmd->cmd->str);
	if (!data->exec->path)
	{
	// TODO: command not found needs to be printed to stderr (in all cases not only here)
		ft_putstr_fd("minishell: command not found\n", 2);
		//printf("minishell: command %s not found\n", cmd->cmd->str);
		exit_child(data, 127);	
	}
	execve(data->exec->path, cmd->args_exec, data->mod_env);
	if (data->exec->path[0] == '/' || data->exec->path[0] == '.')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		//printf("minishell: command '%s' not found\n", data->exec->path);
		exit_child(data, 127);
	}
	exit_child(data, 126);

}

//add built-ins use built in all rounder if == 0 exit, fds will be restored in main
void	complex_exec(t_bigshell *data)
{
	t_command	*current_cmd;

	current_cmd = data->commands;
	while (current_cmd->next)
	{
		if (g_sig == SIGINT) //check for signal before executing any command. if yes, spit prompt again
			CRITICAL_FAILURE(data, "complex exec: SIGINT received");
		if (current_cmd == data->commands)
		{
			if (pipe(data->pipe_fd) == -1)
				CRITICAL_FAILURE(data, "complex exec: pipe failed in first command");
			data->pipe->read = data->pipe_fd[0];
			data->pipe->write = data->pipe_fd[1];
			//dprintf(2, "pipe from first: %d, %d\n", data->pipe_fd[0], data->pipe_fd[1]);
			if ((current_cmd->pid = fork()) == -1)
				CRITICAL_FAILURE(data, "complex exec: fork failed in first command");
			if (current_cmd->pid == 0)
				first_executor(data, current_cmd, data->pipe->write);
			if (close(data->pipe->write) == -1)
				CRITICAL_FAILURE(data, "complex exec: close(1) failed in parent process");
		}
		else
		{
			if (pipe(data->pipe_fd2) == -1)
				CRITICAL_FAILURE(data, "complex exec: pipe 2 failed in middle command");
			//dprintf(2, "pipe from middle: %d, %d\n", data->pipe_fd2[0], data->pipe_fd2[1]);
			data->pipe->write = data->pipe_fd2[1];
			if ((current_cmd->pid = fork()) == -1)
					CRITICAL_FAILURE(data, "complex exec: fork failed in middle command");
			if (current_cmd->pid == 0)
				middle_executor(data, current_cmd, data->pipe->write, data->pipe->read);
			if (close(data->pipe->write) == -1 || close(data->pipe->read) == -1)
				CRITICAL_FAILURE(data, "complex exec: close(1) failed in parent process");
			data->pipe->read = data->pipe_fd2[0];
		}
		current_cmd = current_cmd->next;
	}
	//wait_for_children(data);
	if (!current_cmd->next)
	{
		if (g_sig == SIGINT) //check for signal before executing any command. if yes, spit prompt again
			CRITICAL_FAILURE(data, "complex exec: SIGINT received");
		restore_output(data);
		if ((current_cmd->pid = fork()) == -1)
			CRITICAL_FAILURE(data, "complex exec: fork failed in last command");
		if (current_cmd->pid == 0)
			last_executor(data, current_cmd, data->pipe->read);
		//dprintf(2, "pipe from last: %d\n", data->pipe->read);
		if (close(data->pipe->read) == -1)
			CRITICAL_FAILURE(data, "complex exec: close(0) failed in parent process");
	}
	wait_for_children(data);
}
