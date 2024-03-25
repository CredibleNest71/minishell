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
void	complex_exec(t_bigshell *data, int cmd_pos)
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
}
//only 1 pipe for i == 0 or i == num_cmd
//middle cmd needs 2
