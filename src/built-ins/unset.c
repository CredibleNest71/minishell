/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:00:47 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/23 13:46:07 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <strings.h>

void	unset_var(t_bigshell *data)
{
	o
}

void	ft_unset(t_bigshell *data)
{
	int		len;
	t_env	*current;
	t_env	*current_env;
	
	if (!data->commands->args)
		exit(0);
	current = data->s_env;
	current_env = data->env;
	while (data->commands->args)
	{
		len = ft_strlen(data->commands->args->str);
		while (current && current_env)
		{
			if (ft_strncmp(data->commands->args->str, current->str, len) == 0)
				ft_unset(data);
			if (ft_strncmp(data->commands->args->str, current_env->str, len) == 0)
				ft_unset(data);
			current = current->next;
			current_env  = current_env->next;
		}
	}
}
