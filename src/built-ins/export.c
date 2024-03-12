/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/12 18:11:25 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <stdio.h>

//when u run export with no args, env sorted alphabetically should be printed
//+ variables

int	check_if_sorted(t_env *current)
{
	if (ft_strncmp(current->var, current->next->var, 1) > 0)
		return (1);
	else
	 	return (0);
}

void	switch_values(t_env *current)
{
	char	*tmp;

	tmp = current->var;
	current->var = current->next->var;
	current->next->var = tmp;
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
	while (head)
	{
		printf("%s", head->var);
		printf("=");
		printf("%s\n", head->value);
		head = head->next;
	}
}

void	make_copy(t_bigshell *data)
{
	t_env	*current;
	t_env	*current_env;
	//int		i;

	//i = -1;
	//if (!data->s_env) //check that s-env is empty
		data->s_env = create_node(data, data->env->str);
	current = data->s_env;
		current_env = data->env->next;
		while (current_env)
		{
			current->next = create_node(data, current_env->str);
			current = current->next;
			current_env = current_env->next;
			data->reference_i++;
		}
		sort_env(data);
		return ;
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
		data->exit_stat = 0;
		return ;
	}
	current = data->s_env;
	current_env = data->env;
	arg = data->commands->args;
	while (current->next && current_env->next)
	{
		current = current->next;
		current_env = current_env->next;
	}
	while (arg)
	{
		current->next = create_node(data, arg->str);
		current_env->next = create_node(data, arg->str);
		current = current->next;
		current_env = current_env->next;
		arg = arg->next;
	}
	sort_env(data);
}
