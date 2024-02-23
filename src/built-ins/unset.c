/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:00:47 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/23 15:20:39 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <strings.h>

void	unset_var(t_bigshell *data, t_env *current, t_env *prev)
{
	if (current == data->env || current == data->s_env) //check if head needs to be deleted
	{
		current = current->next;
		if (current == data->env)
			data->env = current;
		else
			data->s_env = current;
		free(current);
	}
	else if (!current->next) //check if last node needs to be deleted
	{
		free(current);
		prev->next = NULL;
	}
	else if (current->next)
	{
		prev->next = current->next;
		free(current);
	}
	print_env(data->s_env);
	data->exit_stat = 0;
	exit (data->exit_stat);
}

void	ft_unset(t_bigshell *data)
{
	int		len;
	t_env	*current;
	t_env	*prev;
	t_env	*current_env;
	t_env	*prev_env;
	
	if (!data->commands->args)
		exit(0);
	current = data->s_env;
	prev = data->s_env;
	current_env = data->env;
	prev_env = data->env;
	while (data->commands->args)
	{
		len = ft_strlen(data->commands->args->str);
		while (current && current_env)
		{
			if (ft_strncmp(data->commands->args->str, current->str, len) == 0)
				unset_var(data, current, prev);
			if (ft_strncmp(data->commands->args->str, current_env->str, len) == 0)
				unset_var(data, current_env, prev_env);
			prev = current;
			current = current->next;
			prev_env = current_env;
			current_env  = current_env->next;
		}
	}
}
