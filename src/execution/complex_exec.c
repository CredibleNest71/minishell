/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:43:53 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/06 10:45:10 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* void	pipe_fork(t_bigshell *data)
{
	if (pipe(data->pipe_fd) == -1)
		CRITICAL_FAILURE(data, "complex exec: pipe failed");
	data->id = fork();
	if (data->id == -1)
		CRITICAL_FAILURE(data, "complex exec: fork failed");
	if (data->id == 0) //child process
	{
		//do shit
	}
	wait(NULL);
} */

/* void	pipe_maker(t_bigshell *data) vad idea no int **
{

} */

//void	execute_2_cmds()

//what happens if there are multiple cmds but no pipes??? check main will it still act as if its being piped???
// I need to check for first cmd and create pipe
//then ill check for middle if encountered I overwrite stdout, otherwise I dont

void	pipe_init(t_bigshell *data)
{
	t_pipe	*pipe;

	pipe = malloc (sizeof(t_pipe));
	if (!pipe)
		CRITICAL_FAILURE(data, "pipe_init: malloc fail");
	data->pipe = pipe;
}

int	get_exit_stat(t_bigshell *data)
{
	t_env	*tmp;
	int		stat_loc;

	tmp = data->env;
	stat_loc = 0;
	while (tmp)
	{
		if (strncmp(tmp->var, "?", ft_strlen(tmp->var)) == 0)
		{
			stat_loc = atoi(tmp->value);
			return (stat_loc);
		}
		tmp = tmp->next;
	}
	return (stat_loc);
}

void	wait_for_children(t_bigshell *data)
{
	t_command	*cmd;
	int			stat_loc;

	cmd = data->commands;
	stat_loc = get_exit_stat(data);
	while (cmd)
	{
		waitpid(cmd->pid, &stat_loc, 0);
		cmd = cmd->next;
	}
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
}

void	first_executor(t_bigshell *data, t_command *cmd, int out_fd)
{
	char	**paths;
	char	*correct_path;

	////printf("first exec:: current command: %s curr arg: %s\n");
	//out_fd = 0;
	paths = NULL;
	correct_path = NULL;
	if (dup2(out_fd, 1) == -1 || close(data->pipe->read) == -1) //|| close(data->pipe->write) == -1
		CRITICAL_FAILURE(data, "complex exec: first executor: dup2 failed");
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //handle correctly
	correct_path = check_if_correct_path(paths, data, cmd->cmd->str);
	if (!correct_path)
		printf("minishell: command %s not found\n", cmd->cmd->str);
	execve(correct_path, cmd->args_exec, data->mod_env);
	//printf("execve failed\n");
	free(correct_path);
	exit(126);

}

void	last_executor(t_bigshell *data, t_command *cmd, int in_fd)
{
	char	**paths;
	char	*correct_path;

	//in_fd = 0;
	paths = NULL;
	correct_path = NULL;
	if (dup2(in_fd, 0) == -1 ) //|| close(data->pipe->write) == -1 || close(data->pipe->read) == -1
		CRITICAL_FAILURE(data, "complex exec: last executor: dup2 failed");
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //handle correctly
	correct_path = check_if_correct_path(paths, data, cmd->cmd->str);
	if (!correct_path)
		printf("minishell: command %s not found\n", cmd->cmd->str);
	execve(correct_path, cmd->args_exec, data->mod_env);
	//printf("execve failed\n");
	free(correct_path);
	exit (126);

}

void	middle_executor(t_bigshell *data, t_command *cmd, int out_fd, int in_fd)
{
	char	**paths;
	char	*correct_path;

	paths = NULL;
	correct_path = NULL;
	if (dup2(in_fd, 0) == -1)
		CRITICAL_FAILURE(data, "complex exec: middle executor: dup2 failed (in_fd)");
	if (dup2(out_fd, 1) == -1 || close(data->pipe->write) == -1 || close(data->pipe->read) == -1)
		CRITICAL_FAILURE(data, "complex exec: middle executor: dup2 failed (out_fd)");
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //handle correctly
	correct_path = check_if_correct_path(paths, data, cmd->cmd->str);
	if (!correct_path)
		printf("minishell: command %s not found\n", cmd->cmd->str);
	execve(correct_path, cmd->args_exec, data->mod_env);
	//printf("execve failed\n");
	free(correct_path);
	exit(126);

}

void	complex_exec(t_bigshell *data)
{
	t_command	*current_cmd;

	current_cmd = data->commands;
	while (current_cmd->next)
	{
		////printf("complex:: current command: %s current arg:%s\n", current_cmd->cmd->str, current_cmd->args->str);
		if (data->commands->input || data->commands->output)
		{
			if (redir(data->commands, data) != 0)
			{
				store_restore_fds(data, 2);
				continue ;
			}
		}
		if (current_cmd == data->commands)
		{
			//im at first command
			////printf("complex: checkpoint first command: %s\n", current_cmd->cmd->str);

			if (pipe(data->pipe_fd) == -1)
				CRITICAL_FAILURE(data, "complex exec: pipe failed in first command");
			data->pipe->read = data->pipe_fd[0];
			data->pipe->write = data->pipe_fd[1];
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
			data->pipe->write = data->pipe_fd2[1];
			if ((current_cmd->pid = fork()) == -1)
				CRITICAL_FAILURE(data, "complex exec: fork failed in middle command");
			if (current_cmd->pid == 0)
				middle_executor(data, current_cmd, data->pipe->write, data->pipe->read);
			if (close(data->pipe->write) == -1)
				CRITICAL_FAILURE(data, "complex exec: close(1) failed in parent process");
			data->pipe->read = data->pipe_fd2[0];
		}
		// wait(NULL);
		current_cmd = current_cmd->next;
	}
	wait_for_children(data);
	if (!current_cmd->next)
	{
		if (data->commands->input || data->commands->output)
		{
			if (redir(data->commands, data) != 0)
			{
				store_restore_fds(data, 2);
				return ;
			}
		}
		if ((current_cmd->pid = fork()) == -1)
			CRITICAL_FAILURE(data, "complex exec: fork failed in last command");
		if (current_cmd->pid == 0)
		{
			last_executor(data, current_cmd, data->pipe->read);
		}
		////printf("i happened \n");
		if (close(data->pipe->read) == -1)
			CRITICAL_FAILURE(data, "complex exec: close(0) failed in parent process");
	}
	wait_for_children(data);
}

/*void	complex_exec(t_bigshell *data)
{
	// if data->cmd_num == 2 
	// else
	//cmds are store in linked list maybe iterate throught them here as long as a cmd->next exists
	if (cmd_pos == 0) //first cmd //maybe check here if data->cmd == head
	{
		//open pipe & write into it
		if (pipe(data->pipe_fd) == -1)
			CRITICAL_FAILURE(data, "pipe failed");
		if ((data->id = fork()) == -1)
			CRITICAL_FAILURE(data, "complex exec: fork failed in 1st cmd");
		if (data->id == 0)
			//execute cmd
		close(data->pipe_fd[1]);
	}
	if (cmd_pos > 0 && cmd_pos < data->num_cmd) //middle cmd //maybe if data->cmd->next exists
	{
		//read from previos pipe and open new one
		if ((data->id = fork()) == -1)
			CRITICAL_FAILURE(data, "complex exec: fork failed in middle cmd");
		if (data->id == 0)
			//execute cmd
		close(data->pipe_fd[0]);
		if (pipe(data->pipe_fd) == -1)
			CRITICAL_FAILURE(data, "pipe failed");
	}
	else //maybe if (!cmd->next && cmd != head)
	{
		//read from pipe
	}
}*/
//only 1 pipe for i == 0 or i == num_cmd
//middle cmd needs 2
