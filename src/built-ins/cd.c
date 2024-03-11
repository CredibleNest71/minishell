/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/11 12:58:59 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>

//relative or absolute path
//if only cd was called, go to home directory
//update env after chdir gets executed

/*enum type {
	ARG = 0,
	PATH,
	SEP,
} typedef e_type;*/

void	ft_cd(t_bigshell *data)
{
	char	*path;
	char	*cwd; //somehow dynamically allocate this
	//int		getcwd_result;
	size_t	buffer_size;
	
	if (data->commands->arg_num > 1)
		simple_error(data, 1); //perror prints "success"? should be too many args
	if (!data->commands->args || ft_strncmp(data->commands->args->str, "~", 1) == 0)
		path = getenv("HOME");

	if (ft_strncmp(data->commands->args->str, "..", 2) == 0)
	{
		buffer_size = BUFFER;
		while (1)
		{
			if (cwd)
				break ;
			cwd = malloc(sizeof(char) * BUFFER);
			if (!cwd)
				fatal_error(data, 1); //free cwd!
			cwd = getcwd(cwd, buffer_size);
			if (!cwd && errno == ERANGE)
			{
				//simple_error(data, 1); //perror: unable to get current dir
				free(cwd);
				buffer_size += BUFFER_INCREMENT;
			}
			if (!cwd && errno != ERANGE)
				simple_error(data, 1); // unable to get current directory
		}
		
		//delete everything including and after the last /
		
		getcwd again
		chdir (cwd);
		free(cwd);
	} */
	// else (data->commands->args[0])
	//	path = data->commands->args[0]->str;
	if (chdir(path) == -1)
		perror("cd failure:");
	return ;
}

/* void	ft_cd(t_bigshell *data, int index)
{
	char	*path;
	if (data->commands[index]->cmd->type == (e_type) PATH)
		path = data->commands[index]->cmd->str;
	else
		path = getenv("HOME");
	if (chdir(path) == -1)
		perror("cd failure:");
	exit (0);
} */