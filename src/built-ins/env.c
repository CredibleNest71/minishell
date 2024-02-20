/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:01:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/15 19:35:34 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//what should happen if env -i is run?
//how does env work with args?

void	add_env_variable(t_bigshell *data)
{
	//if we make data->env a linked list maybe its better
	int	i;

	i = 0;
	while (data->env[i])
		i++;
	data->env = malloc((i + 1) * sizeof(char *)); //protect
	data->env[i++] = data->export_var;
	data->env[i] = NULL;
	data->exit_stat = 0;
	exit(data->exit_stat);
}

//env should be a linked list and if export is used, add variable randomly

void	ft_env(t_bigshell *data, int option)
{
	int	i;
	if (option == 1)
		add_env_variable(data);
	if (data->commands->arg_num == 0)
	{
		i = 0;
		while (data->env[i] != NULL)
			printf("%s\n", data->env[i++]);
		exit(0);
	}
	exit(0);
}
