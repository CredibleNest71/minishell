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

void	pipe_fork(t_bigshell *data)
{
	if (pipe(data->pipe_fd) == -1)
	{
		printf("pipe failed\n");
		fatal_error(data, 1);
	}
	data->id = fork();
	if (data->id == -1)
	{
		printf("fork failed\n");
		fatal_error(data, 1);
	}
	if (data->id == 0) //child process
	{
		//do shit
	}
}

void	complex_exec(t_bigshell *data, t_token *cmd)
{
	//simple_exec(data);
}
