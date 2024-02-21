/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/21 12:02:50 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>

//when u run export with no args, env sorted alphabetically should be printed
//+ variables

int	check_if_sorted(t_env *current)
{
	if (ft_strncmp(current->str, current->next->str, 1) > 0)
		return (1);
	else
	 	return (0);
}

void	switch_values(t_env *current)
{
	char	*tmp;

	tmp = current->str;
	current->str = current->next->str;
	current->next->str = tmp;
}

void	sort_env(t_bigshell *data)
{
	t_env	*env_i;
	t_env	*env_j;

	env_i = data->s_env;
	while (env_i->next)
	{
		env_j = data->s_env;
		while (env_j->next)
		{
			if (check_if_sorted(env_j) == 1)
				switch_values(env_j);
			env_j = env_j->next;
		}
		env_i = env_i->next;
	}
}

void	print_env(t_env *head)
{
	while (head->next)
	{
		printf("%s\n", head->str);
		head = head->next;
	}
}

void	make_copy(t_bigshell *data)
{
	t_env	*current;
	t_env	*current_env;

	data->s_env = create_node(data, data->env->str);
	current = data->s_env;
	current_env = data->env;
	while (current_env->next)
	{
		current = create_node(data, current_env->str);
		current = current->next;
		current_env = current_env->next; 
	}
}

void	ft_export(t_bigshell *data)
{
	int		i;
	t_env	*current;
	if (!data->commands->args)
	{
		//store_env(data, data->s_env, data->og_env); //wont work, make copy of linked list
		make_copy(data);
		sort_env(data);
		print_env(data->s_env);
		data->exit_stat = 0;
		exit (data->exit_stat);
	}
	i = -1;
	current = data->env;
	while (current->next)
		current = current->next;
	while (++i < data->commands->arg_num)
		current->next = create_node(data, data->commands->args[i].str);
}
