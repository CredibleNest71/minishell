/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/23 15:19:29 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <stdio.h>

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
	while (head)
	{
		printf("%s\n", head->str);
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
	//if (option == 0)
	//{
	//	data->reference_i++;
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
	//}
	/* while (current)
		current = current->next;
	current_env = data->env;
	while (++i < data->reference_i)
		current_env = current_env->next;
	sort_env(data); */
}

/* int	check_reference(t_bigshell *data)
{
	int	i;
	
	if (data->reference_i == 0) //reference_i should be initialized to 0 at very beginning
		return (0); //option is 0 if s_env is empty
	i = 0;
	while (data->env)
	{
		i++;
		data->env = data->env->next;
	}
	printf("i = %d\n", i);
	if (data->reference_i < i)
		return (1); //option is 1 if theres new nodes
	if (data->reference_i == i) //is this condition necessary later on (outside of testing)
		return (3);
	return (2); //2 if error bc wtf
} */

void	ft_export(t_bigshell *data)
{
	//int		i;
	//int		option;
	t_env	*current;
	t_env	*current_env;
	
	//option = check_reference(data);
/* 	if (option == 2)
		simple_error(data, 1); */
	if (!data->s_env)
		make_copy(data);
	if (!data->commands->args)
	{
		//store_env(data, data->s_env, data->og_env); //wont work, make copy of linked list
		//make_copy(data);
		print_env(data->s_env);
		data->exit_stat = 0;
		exit (data->exit_stat);
	}
	//i = -1;
	current = data->s_env;
	current_env = data->env;
	while (current->next && current_env->next)
		current = current->next;
	//printf("a %s\n", data->commands->args->next->str);
	while (data->commands->args)
	{
	//	printf("%s\n", current->str);
		current->next = create_node(data, data->commands->args->str);
		current_env->next = create_node(data, data->commands->args->str);
	//	printf("%s\n", current->next->str);
		current = current->next;
		current_env = current_env->next;
		data->commands->args = data->commands->args->next;
	}
	sort_env(data);
	//print_env(data->s_env);
	exit (1);
}
