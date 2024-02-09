/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:01:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/09 12:42:21 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//what should happen if env -i is run?
//how does env work with args?

void	ft_env(t_bigshell *data, int index)
{
	int	i;
	if (data->commands[index]->arg_num == 0)
	{
		i = 0;
		while (data->env[i] != NULL)
			printf("%s\n", data->env[i++]);
		exit(0);
	}
	exit(0);
}