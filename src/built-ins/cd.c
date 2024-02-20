/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/09 15:47:27 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>

//relative or absolute path
//if only cd was called, go to home directory
//update env after chdir gets executed

void	ft_cd(t_bigshell *data, int index)
{
	char	*path;
	char	*cwd; //somehow dynamically allocate this
	if (data->commands[index]->arg_num > 1)
		simple_error(data, 1); //for whatever reason perror prints "success"?
	if (!data->commands[index]->args)
		path = getenv("HOME");

	if (ft_strncmp(data->commands[index]->args[0]->str, "..", 2) == 0)
	{
		cwd = getcwd(cwd, sizeof(cwd));
		//delete everything including and after the last /
		
		getcwd again
		chdir (cwd);
		free(cwd);
	}
	/* else (data->commands[index]->args[0])
		path = data->commands[index]->args[0]->str; */
	if (chdir(path) == -1)
		perror("cd failure:");
	exit(0);
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