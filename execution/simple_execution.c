/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/01 12:04:02 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <unistd.h>

void	simple_exec(t_command **command)
{
	int		s_pid;
	char	*path;

	if (command->input || command->output)
		redir(command[0]);
	path = builtin_exec();
	if (!path) //possibly will return null if builtin was found
	execve(const char *path, char *const *argv, char *const *envp);
	//protect execve
}
