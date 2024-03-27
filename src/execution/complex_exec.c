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

void	first_executor(t_bigshell *data, char *cmd, int out_fd)
{
	char	**paths;
	char	*correct_path;

	if (dup2(out_fd, 1) == -1)
		CRITICAL_FAILURE(data, "complex exec: first executor: dup2 failed");
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //handle correctly
	correct_path = check_if_correct_path(paths, data, cmd);
	if (!correct_path)
		printf("minishell: command %s not found\n", cmd);
	execve(correct_path, data->commands->args_exec, data->mod_env);
	printf("execve failed\n");
	free(correct_path);

}

void	last_executor(t_bigshell *data, char *cmd, int in_fd)
{
	char	**paths;
	char	*correct_path;

	if (dup2(in_fd, 0) == -1)
		CRITICAL_FAILURE(data, "complex exec: last executor: dup2 failed");
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //handle correctly
	correct_path = check_if_correct_path(paths, data, cmd);
	if (!correct_path)
		printf("minishell: command %s not found\n", cmd);
	execve(correct_path, data->commands->args_exec, data->mod_env);
	printf("execve failed\n");
	free(correct_path);

}

void	middle_executor(t_bigshell *data, char *cmd, int out_fd, int in_fd)
{
	char	**paths;
	char	*correct_path;

	if (dup2(in_fd, 0) == -1)
		CRITICAL_FAILURE(data, "complex exec: middle executor: dup2 failed (in_fd)");
	if (dup2(out_fd, 1) == -1)
		CRITICAL_FAILURE(data, "complex exec: middle executor: dup2 failed (out_fd)");
	convert_env(data);
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //handle correctly
	correct_path = check_if_correct_path(paths, data, cmd);
	if (!correct_path)
		printf("minishell: command %s not found\n", cmd);
	execve(correct_path, data->commands->args_exec, data->mod_env);
	printf("execve failed\n");
	free(correct_path);

}

void	complex_exec(t_bigshell *data)
{
	t_command	*current_cmd;

	current_cmd = data->commands;
	while (current_cmd->next)
	{
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
			if (pipe(data->pipe_fd) == -1)
				CRITICAL_FAILURE(data, "complex exec: pipe failed in first command");
			data->pipe->read = data->pipe_fd[0];
			data->pipe->write = data->pipe_fd[1];
			if ((data->id = fork()) == -1)
				CRITICAL_FAILURE(data, "complex exec: fork failed in first command");
			if (data->id == 0)
				first_executor(data, current_cmd->cmd->str, data->pipe->write);
		}
		else
		{
			if (pipe(data->pipe_fd2) == -1)
				CRITICAL_FAILURE(data, "complex exec: pipe 2 failed in middle command");
			data->pipe->write = data->pipe_fd2[1];
			if ((data->id = fork()) == -1)
				CRITICAL_FAILURE(data, "complex exec: fork failed in middle command");
			if (data->id == 0)
				middle_executor(data, current_cmd->cmd->str, data->pipe->write, data->pipe->read);
			data->pipe->read = data->pipe_fd2[0];
		}
		current_cmd = current_cmd->next;
	}
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
		if ((data->id = fork()) == -1)
			CRITICAL_FAILURE(data, "complex exec: fork failed in last command");
		if (data->id == 0)
			last_executor(data, current_cmd->cmd->str, data->pipe->read);
	}
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
