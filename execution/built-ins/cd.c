/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/01/23 12:33:25 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

//relative or absolute path

void	ft_cd(t_command paths)
{
	if (chdir(paths->path) == 0)
	{
		//probably do nothing, check bash
	}
	else {
		perror("cd failure:");
	}
}