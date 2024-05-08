/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/08 19:47:45 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

//when u run export with no args, env sorted alphabetically should be printed
//+ variables

int	check_var(t_bigshell *data, char *key)
{
	char	*end;
	char	*var;
	int		i;

	var = ft_strdup(key);
	if (!var)
		CRITICAL_FAILURE(data, "export: strdup failed");
	end = ft_strchr(var, '=');
	if (end)
		*end = 0;
	i = 0;
	if (!(var[0] == '_' || (var[0] >= 'A' && var[0] <= 'Z') || (var[0] >= 'a' && var[0] <= 'z')))
	{
		free(var);
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		return (update_exit_stat(data, 1), 1);
	}
	while (var[++i])
	{
		if (!(var[i] == '_' || (var[i] >= '0' && var[i] <= '9') || \
		(var[i] >= 'A' && var[i] <= 'Z') || (var[i] >= 'a' && var[i] <= 'z')))
		{
			free(var);
			return (1);
		}
	}
	free(var);
	return (0);
}

void	switch_values(t_bigshell *data, t_env *node, char *new_value, int len)
{
	free(node->value);
	node->value = NULL;
	if (new_value)
	{
		node->value = (char *)malloc(sizeof(char) * len + 1);
		if (!node->value)
			CRITICAL_FAILURE(data, "export: malloc failed");
	}
	ft_memcpy(node->value, new_value, len + 1);
}

int	var_exists(t_bigshell *data, char *str)
{
	t_env	*env;
	t_env	*s_env;
	char	*separator;
	char	*key;
	int		var_len;
	int		i;

	i = 0;
	env = data->env;
	s_env = data->s_env;
	separator = ft_strchr(str, '=');
	if (!separator)
		var_len = ft_strlen(str);
	else
		var_len = separator - str;
	key = malloc(sizeof(char *) * var_len + 1);
	if (!key)
		CRITICAL_FAILURE(data, "malloc failed\n");
	ft_memcpy(key, str, var_len);
	key[var_len] = '\0';
	while (env)
	{
		if (ft_strcmp(env->var, key) == 0)
		{
			if (!separator || *(separator + 1) == '\0')
				switch_values(data, env, NULL, 1);
			else
				switch_values(data, env, separator + 1, ft_strlen(separator + 1));
			i++;
			break ;
		}
		env = env->next;
	}
	while (s_env)
	{
		if (ft_strcmp(s_env->var, key) == 0)
		{
			if (!separator || *(separator + 1) == '\0')
				switch_values(data, s_env, NULL, 1);
			else
				switch_values(data, s_env, separator + 1, ft_strlen(separator + 1));
			i++;
			break ;
		}
		s_env = s_env->next;
	}
	free(key);
	if (i == 2)
		return (0);
	return (1);
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
		current_env->next = create_node(data, arg->str);
		current = current->next;
		current_env = current_env->next;
		arg = arg->next;
		data->var_i++;
	}
	sort_env(data);
	return (update_exit_stat(data, 0));
}
