/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:05:40 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/13 13:04:57 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>

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

void	store_exit_code(t_bigshell *data, int memo) //if smt drastically fails, free and exit minishell. (memory allocation fail, fork fail, dup, etc)
{
	data->exit_stat = memo;
	
}

void	error_handler(char	*message) //irrelevant, unless critical fail: store exit status and return prompt, otherwise call free fucntion and exit minishell
{
	printf("Failure: %s", message);
	//call exit code function(?)
	//new prompt
}

/* void	complex_exec(t_bigshell *data, int index) //do I want to modify the struct?
{
	int	j;

	j = 0;
	while (++index <= data->num_cmd)
	{
		if (data->commands[index]->input || data->commands[index]->output)
			redir(data->commands[index], data);
	}
	
} */

//doing this in main:
		/* while (i <= data->num_cmd) //tf?
		{
			pid = fork();
			if (pid == 0) //child
				printf("child");
				//execute cmd;
				//remember to handle error (send correct exit code)
			if (pid == -1) //fork failed (check errno?)
				printf("failed child");
				//handle error (send correct exit code)
			//probably close fds;
			//wait_for_offspring(struct);
		} */