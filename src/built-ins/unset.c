/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:00:47 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/27 15:35:37 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void	unset_var(t_bigshell *data, t_env **current, t_env **prev)
{
	t_env	*tmp;

	tmp = NULL;
	if (*current == data->env || *current == data->s_env) //check if head needs to be deleted
	{
		if (*current == data->env)
			data->env = (*current)->next;
		else
			data->s_env = (*current)->next;
		tmp = *current;
		*current = (*current)->next;
		free(tmp); //need ft to properly free
		return ;
	}
	if (!(*current)->next) //check if last node needs to be deleted
	{
		free((*current));
		(*prev)->next = NULL;
		return ; //need to exit here;
	}
	else
	{
		//printf("c %s\n", (*prev)->str);
		//printf("c %s\n", (*current)->next->str);
		(*prev)->next = (*current)->next;
		free(*current);
		//*current = (*prev)->next;
		//printf("c %s\n", (*current)->str);
	//printf("a\n");
		return ;
	}
}

void	find_node_to_delete(t_bigshell *data, t_env **current, t_env **prev, int len, t_token *arg)
{
	while (*current)
	{
		/* if (!data->commands->args)
			return ; */
		//printf("%s\n", arg->str);
		if (ft_strncmp(arg->str, (*current)->str, len) == 0)
		{
				//printf("i\n");
			unset_var(data, current, prev);
			return ;
		//*prev = (*current)->next;
		//free(*current);
		//*current = (*prev)->next;
		//printf("(*current): %s\n", (*current)->str);
				
		}
		else
		{		
			*prev = *current;
			*current = (*current)->next;
		}
	}
	return ;
}

void	ft_unset(t_bigshell *data)
{
	int		len;
	t_env	*current;
	t_env	*prev;
	t_env	*current_env;
	t_env	*prev_env;
	t_token	*arg;
	
	if (!data->commands->args)
		return ;
	current = data->s_env;
	prev = NULL;
	current_env = data->env;
	prev_env = NULL;
	arg = data->commands->args;
	while (arg)
	{
		len = ft_strlen(data->commands->args->str);
		find_node_to_delete(data, &current, &prev, len, arg);
		find_node_to_delete(data, &current_env, &prev_env, len, arg);
		arg = arg->next;
		current = data->s_env;
		current_env = data->env;
	}
	return ;
}

/* void	ft_unset(t_bigshell *data)
{
	int		len;
	t_env	*current;
	t_env	*prev;
	t_env	*current_env;
	t_env	*prev_env;
	
	if (!data->commands->args)
		return ; //don't exit minishell (unset shouldn't be in a child process)
	current = data->s_env;
	prev = NULL;
	current_env = data->env;
	prev_env = NULL;
	while (data->commands->args)
	{
		//print_env(data->s_env);
		len = ft_strlen(data->commands->args->str);
		while (current && current_env) //flawed theyre not identical
		{
			if ((ft_strncmp(data->commands->args->str, current->str, len) == 0) ||
			(ft_strncmp(data->commands->args->str, current_env->str, len) == 0))
			{
				//printf("current str: %s\n", current->str);
				if (ft_strncmp(data->commands->args->str, current->str, len) == 0)
				{
					unset_var(data, current, prev); 
					prev = current->next;
					free(current);
					current = prev;
					//printf("current is: %s\n", current->str);
				}
				//printf("current env str: %s\n", current_env->next->str);
				if (ft_strncmp(data->commands->args->str, current_env->str, len) == 0)
				{
					//printf("b\n");
					unset_var(data, current_env, prev_env);
					prev_env = current_env;
					current_env  = current_env->next;
					free(current_env);
				}
			}
	// 		if (ft_strncmp(data->commands->args->str, current_env->str, len) == 0)
				unset_var(data, current_env, prev_env); //
			else
			{
				prev = current;
				current = current->next;
				prev_env = current_env;
				current_env  = current_env->next;
			}
		}
		data->commands->args = data->commands->args->next;
	}
	return ;
	//exit(0); //actually exit here child process
} */