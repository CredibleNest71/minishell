/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/09 10:53:48 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

//relative or absolute path
//if only cd was called, go to home directory
//update env after chdir gets executed

/*enum type {
	ARG = 0,
	PATH,
	SEP,
} typedef e_type;*/

void	ft_cd(t_bigshell *data, int index)
{
	char	*path;
	if (data->commands[index]->arg_num > 1)
		simple_error(data, 1);
	if (!data->commands[index]->args)
		path = getenv("HOME");

	if (ft_strncmp(data->commands[index]->args[0]->str, "..", 2) == 0)
		//go one back;
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