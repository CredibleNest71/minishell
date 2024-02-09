/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:04 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/09 10:57:11 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_pwd(t_bigshell *data)
{
	char	*cwd;

	cwd = getenv("PWD");
	if (!cwd)
	{
		ft_putstr_fd("Current Working Directory Not Found", 1);
		data->exit_stat = 1;
		exit(data->exit_stat);
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	exit(0);
}
