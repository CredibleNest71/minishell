/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:05:40 by ischmutz          #+#    #+#             */
/*   Updated: 2024/01/30 13:58:12 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// use 0 for success, as for other shit check bash exit codes

//if redirection == NULL
//use stdin, stdout & stderr

/* void	wait_for_offspring(//struct)
{
	waitpid(//struct->id, &data->exitstatus, 0);
	waitpid(//struct->id2, &data->exitstatus, 0);
	if (WIFEXITED(//struct->exitstatus))
		//struct->exitstatus = WEXITSTATUS(//struct->exitstatus);
} */

void	builtin_exec(/*cmd arg*/)
{
	// check if cmd is empty
	// check if cmd is one of the built-ins
		// store cmd names with  
}

void	redir(t_command *cmd)
{
	if (cmd->output) // redirecting output
	{
		
	}
	if (cmd->input) // redirecting input
	{
		if (check_file() == -1)
			//print "file does not exist"
	}
}

void	exec(t_command *cmd_table) //do I want to modify the struct?
{
	int	pid;
	int	i;

	i = 0;
	if (redirection == yes)//check for redirection
		//dup2 the shit outta this
		redir();
	if (cmd_table->cmd[i] && !(cmd_table->cmd[i + 1])) //check if there's only one command or check that no pipes exist
		//builtin_exec(cmd arg);
	while (i < cmd_table->arg_num)
	{
		pid = fork();
		if (pid == 0) //child
			//execute cmd;
			//remember to handle error (send correct exit code)
		if (pid == -1) //fork failed (check errno?)
			//handle error (send correct exit code)
		//probably close fds;
		//wait_for_offspring(struct);
	}
}