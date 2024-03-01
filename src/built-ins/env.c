/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:01:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/01 11:28:26 by ischmutz         ###   ########.fr       */
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
	while (data->og_env[i])
		i++;
	data->og_env = malloc((i + 1) * sizeof(char *)); //protect
	data->og_env[i++] = data->export_var;
	data->og_env[i] = NULL;
	data->exit_stat = 0;
	//exit(data->exit_stat);
	return ;
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
