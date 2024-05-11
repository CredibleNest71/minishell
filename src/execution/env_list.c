/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:46:40 by a                 #+#    #+#             */
/*   Updated: 2024/05/11 16:07:21 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*create_var(t_bigshell *data, char *str)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		critical_failure(data, "env_list: malloc failed 1");
	new_node->var = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_node->var)
		critical_failure(data, "env_list: malloc failed 2");
	new_node->var = ft_strdup(str);
	if (!new_node->var)
		critical_failure(data, "env_list: strdup failed 1");
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*create_node(t_bigshell *data, char *str)
{
	t_env	*new_node;
	char	*separator;
	int		var_len;
	int		value_len;

	separator = ft_strchr(str, '=');
	if (!separator)
		return (create_var(data, str));
	var_len = separator - str;
	value_len = ft_strlen(separator + 1);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		critical_failure(data, "env_list: malloc failed 3");
	new_node->var = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!new_node->var)
		critical_failure(data, "env_list: malloc failed 4");
	ft_memcpy(new_node->var, str, var_len);
	new_node->var[var_len] = '\0';
	new_node->value = (char *)malloc(sizeof(char) * (value_len + 1));
	if (!new_node->value)
		critical_failure(data, "env_list: malloc failed 5");
	ft_memcpy(new_node->value, separator + 1, value_len);
	new_node->value[value_len] = '\0';
	new_node->next = NULL;
	return (new_node);
}

//this ft stores the initial env given when the executable is 1st ran
void	store_env(t_bigshell *data, char **env)
{
	int		i;
	t_env	*current_node;

	i = 0;
	if (!env || !env[0])
	{
		data->env = create_node(data, "?=0");
		data->var_i = 1;
	}
	else
	{
		data->env = create_node(data, env[i]);
		current_node = data->env;
		while (env[++i])
		{
			current_node->next = create_node(data, env[i]);
			current_node = current_node->next;
		}
		current_node->next = create_node(data, "?=0");
		i++;
		data->var_i = i;
	}
}

int	strlen_env(t_bigshell *data)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = data->env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	convert_env(t_bigshell *data)
{
	int		i;
	char	*str;
	char	*tmp;
	t_env	*current;

	data->mod_env = (char **)malloc(sizeof(char *) * (strlen_env(data) + 1));
	if (!data->mod_env)
		critical_failure(data, "env_list: malloc failed 6");
	data->mod_env[strlen_env(data)] = NULL;
	i = 0;
	current = data->env;
	while (current)
	{
		tmp = ft_strjoin(current->var, "=");
		if (!tmp)
			simple_error(data, 1);
		str = ft_strjoin(tmp, current->value);
		free(tmp);
		if (!str)
			simple_error(data, 1);
		data->mod_env[i] = ft_strdup(str);
		if (!data->mod_env[i])
			critical_failure(data, "env_list: strdup failed 2");
		free(str);
		current = current->next;
		i++;
	}
}
