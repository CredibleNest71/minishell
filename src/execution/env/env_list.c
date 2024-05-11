/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:46:40 by a                 #+#    #+#             */
/*   Updated: 2024/05/11 18:14:59 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

static char	**allocate_mod_env(t_bigshell *data)
{
	char	**mod_env;

	mod_env = (char **)malloc(sizeof(char *) * (strlen_env(data) + 1));
	if (!mod_env)
		critical_failure(data, "env_list: malloc failed 6");
	mod_env[strlen_env(data)] = NULL;
	return (mod_env);
}

void	convert_env(t_bigshell *data)
{
	int		i;
	char	*str;
	char	*tmp;
	t_env	*current;

	data->mod_env = allocate_mod_env(data);
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
