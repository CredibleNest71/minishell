/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/14 12:08:40 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <stdio.h>

//when u run export with no args, env sorted alphabetically should be printed
//+ variables

//checks the first letter of the var name
int	check_if_sorted(t_env *current)
{
	if (ft_strncmp(current->var, current->next->var, 1) > 0)
		return (1);
	else
	 	return (0);
}

//switches the contents of the node
void	switch_values(t_env *current)
{
	char	*tmp_var;
	char	*tmp_value;

	tmp_var = current->var;
	tmp_value = current->value;
	
	current->var = current->next->var;
	current->value = current->next->value;
	current->next->var = tmp_var;
	current->next->value = tmp_value;
}

//sorts s_env alphabetically
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

//prints env when export no args is called
void	print_env(t_env *head)
{
	while (head)
	{
		printf("declare -x ");
		printf("%s", head->var);
		printf("=");
		printf("%s\n", head->value);
		head = head->next;
	}
}

/* data->s_env = create_node(data, data->env->str);
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
	return ; */
	//
	//
	//weird make_copy I modified for var&value struct
	/* t_env	*current;
	int		i;

	i = 0;
	//if (!data->s_env) //check that s-env is empty
	convert_env(data);
	printf("\n\n\n\nmod_env:\n");
	while (data->mod_env[i])
		printf("%s\n", data->mod_env[i++]);
	printf("\n\n\n\n");
	i = 0;
	data->s_env = create_node(data, data->mod_env[0]);
	current = data->s_env;
	while (data->mod_env[++i])	
	{
		current->next = create_node(data, data->mod_env[i]);
		current = current->next;
		data->reference_i++;
	}
	sort_env(data);
	return ; */
//copies updated env into s_env & then sorts it
void	make_copy(t_bigshell *data)
{
	t_env	*current;
	t_env	*current_env;
	char	*str;

	str = ft_strjoin(data->env->var, "=");
	if (!str)
		fatal_error(data, 1);
	str = ft_strjoin(str, data->env->value);
	if (!str)
		fatal_error(data, 1);
	//if (!data->s_env) //check that s-env is empty
	data->s_env = create_node(data, str);
	free(str);
	current = data->s_env;
	current_env = data->env->next;
	while (current_env)
	{
		str = ft_strjoin(current_env->var, "=");
		if (!str)
			fatal_error(data, 1);
		str = ft_strjoin(str, current_env->value);
		if (!str)
			fatal_error(data, 1);
		current->next = create_node(data, str);
		free(str);
		current = current->next;
		current_env = current_env->next;
		data->reference_i++;
	}
	sort_env(data);
	return ;
}

int	check_var(t_bigshell *data, char *key)
{
	char	*end;
	char	*var;
	int		i;

	var = ft_strdup(key);
	if (!var)
		fatal_error(data, 1);
	end = ft_strchr(var, '=');
	*end = 0;
	i = 0;
	if (!(var[0] == '_' || (var[0] >= 'A' && var[0] <= 'Z') || (var[0] >= 'a' && var[0] <= 'z')))
	{
		free(var);
		return (1);
	}
	while (var[++i])
	{
		if (!(var[i] == '_' || (var[i] >= '0' && var[i] <= '9') || (var[i] >= 'A' && var[i] <= 'Z') ||
		(var[i] >= 'a' && var[i] <= 'z')))
		{
			free(var);
			return (1);
		}
	}
	free(var);
	return (0);
}


// int	var_exist(t_bigshell *data, char *str)
// {
// 	t_env	*env;
// 	t_env	*s_env;

// 	env = data->env;
// 	s_env = data->s_env;
	
// }

void	ft_export(t_bigshell *data)
{
	t_env	*current;
	t_env	*current_env;
	t_token	*arg;
	
	/*if (!data->s_env)*/
		make_copy(data);
	//print_env(data->s_env);
	//printf("after make copy\n\n\n\n");
	if (!data->commands->args)
	{
		//printf("I should be printing twice after this:\n");
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
		if (check_var(data, arg->str) == 1)
			return ;
		// if (var_exist(data, arg->str) == 0)
		// 	continue ;
		current->next = create_node(data, arg->str);
		current_env->next = create_node(data, arg->str);
		current = current->next;
		current_env = current_env->next;
		arg = arg->next;
		data->var_i++;
	}
	sort_env(data);
	//printf("before add &sort:\n\n\n\n");
	//print_env(data->env);
	//printf("after adding var &sort\n\n\n\n");
}
