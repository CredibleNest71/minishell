/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 15:16:13 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static void	add_to_env(t_bigshell *data, t_env *current, t_token *arg)
{
	while (arg)
	{
		if (check_var(data, arg->str) == 1)
			return ;
		if (!var_exists(data, arg->str))
		{
			arg = arg->next;
			continue ;
		}
		current->next = create_node(data, arg->str);
		current = current->next;
		arg = arg->next;
		data->var_i++;
	}
}

void	ft_export(t_bigshell *data)
{
	t_env	*current;
	t_env	*current_env;
	t_token	*arg;

	if (!data->s_env)
		make_copy(data);
	if (!data->commands->args)
	{
		print_env(data->s_env);
		return (update_exit_stat(data, 0));
	}
	current = data->s_env;
	current_env = data->env;
	arg = data->commands->args;
	while (current->next && current_env->next)
	{
		current = current->next;
		current_env = current_env->next;
	}
	add_to_env(data, current, arg);
	add_to_env(data, current_env, arg);
	sort_env(data);
	return (update_exit_stat(data, 0));
}
