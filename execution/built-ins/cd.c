/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/01/24 17:47:58 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

//relative or absolute path
//if only cd was called, go to home directory
//update env after chdir gets executed

void	ft_cd(t_command paths)
{
	char	*path;
	if (paths->args[0]->type == PATH)
		path = paths->args[0]->arg;
	else
		path = getenv("HOME");
	if (chdir(path) == -1)
		perror("cd failure:");
}