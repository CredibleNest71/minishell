/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:34:44 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/04 18:50:00 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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
void	switch_nodes(t_env *current)
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
				switch_nodes(env_j);
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
		if (ft_strncmp(head->var, "?", ft_strlen(head->var)) == 0)
		{
			head = head->next;
			continue ;
		}
		printf("declare -x ");
		printf("%s", head->var);
		if (!head->value)
			printf("=\"\"\n");
		if (head->value)
			printf("=%c%s%c\n", 34, head->value, 34);
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
	char	*tmp;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strjoin(data->env->var, "=");
	if (!tmp)
		CRITICAL_FAILURE(data, "export: strjoin failed 1");
	tmp1 = ft_strjoin(tmp, data->env->value);
	free(tmp);
	if (!tmp1)
		CRITICAL_FAILURE(data, "export: strjoin failed 2");
	data->s_env = create_node(data, tmp1);
	free(tmp1);
	current = data->s_env;
	current_env = data->env->next;
	while (current_env)
	{
		tmp2 = ft_strjoin(current_env->var, "=");
		if (!tmp2)
			CRITICAL_FAILURE(data, "export: strjoin failed 3");
		tmp3 = ft_strjoin(tmp2, current_env->value);
		free(tmp2);
		if (!tmp3)
			CRITICAL_FAILURE(data, "export: strjoin failed 4");
		current->next = create_node(data, tmp3);
		free(tmp3);
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
		CRITICAL_FAILURE(data, "export: strdup failed");
	end = ft_strchr(var, '=');
	if (end)
		*end = 0;
	i = 0;
	if (!(var[0] == '_' || (var[0] >= 'A' && var[0] <= 'Z') || (var[0] >= 'a' && var[0] <= 'z')))
	{
		free(var);
		printf("tinyshell: export: `%s': not a valid identifier\n", key); //key? tiene que ser full string
		return (update_exit_stat(data, 1), 1);
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

/* t_env *check_existence(t_env *node, char *str)
{
	int	len;

	len = ft_strlen(str);
	while (node)
	{
		if (ft_strncmp(node->var, str, len) == 0)
			return (node);
		node = node->next;
	}
}  */

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
		;// well done TODO
	ft_memcpy(key, str, var_len);
	key[var_len] = '\0';
	while (env)
	{
		if (ft_strncmp(env->var, key, ft_strlen(env->var)) == 0)
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
		if (ft_strncmp(s_env->var, key, ft_strlen(s_env->var)) == 0)
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
