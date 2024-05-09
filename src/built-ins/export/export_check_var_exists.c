/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_var_exists.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:45:39 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 19:25:49 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//Functions present in this file:
// -> var-exists -> checks whether the variable already exists in the 
//  environment
// -> switch_values -> switches the value of the variable

//switches the value of the environment variable
void	switch_values(t_bigshell *data, t_env *node, char *new_value, int len)
{
	free(node->value);
	node->value = NULL;
	if (new_value)
	{
		node->value = (char *)malloc(sizeof(char) * len + 1);
		if (!node->value)
			critical_failure(data, "export: malloc failed");
	}
	ft_memcpy(node->value, new_value, len + 1);
}

//goes through env and if the variable is found it swithes its value
//  ->norminette
static int	var_exists3(t_bigshell *data, t_env *env, char *separator,
	char *key)
{
	while (env)
	{
		if (ft_strcmp(env->var, key) == 0)
		{
			if (!separator || *(separator + 1) == '\0')
				switch_values(data, env, NULL, 1);
			else
				switch_values(data, env, separator + 1,
					ft_strlen(separator + 1));
			return (1);
			break ;
		}
		env = env->next;
	}
	return (0);
}

//makes a clone of the enviroments and calls var_exists3 -> norminette
static int	var_exists2(t_bigshell *data, char *separator, char *key)
{
	t_env	*env;
	t_env	*s_env;
	int		i;

	env = data->env;
	s_env = data->s_env;
	i = 0;
	if (var_exists3(data, env, separator, key))
		i++;
	if (var_exists3(data, s_env, separator, key))
		i++;
	free(key);
	if (i == 2)
		return (0);
	return (1);
}

//checks whether the variable already exists in the environment
//& switches the value
int	var_exists(t_bigshell *data, char *str)
{
	char	*separator;
	char	*key;
	int		var_len;

	separator = ft_strchr(str, '=');
	if (!separator)
		var_len = ft_strlen(str);
	else
		var_len = separator - str;
	key = malloc(sizeof(char *) * var_len + 1);
	if (!key)
		critical_failure(data, "malloc failed\n");
	ft_memcpy(key, str, var_len);
	key[var_len] = '\0';
	return (var_exists2(data, separator, key));
}

// int	var_exists(t_bigshell *data, char *str)
// {
// 	t_env	*env;
// 	t_env	*s_env;
// 	char	*separator;
// 	char	*key;
// 	int		var_len;
// 	int		i;
//
// 	i = 0;
// 	env = data->env;
// 	s_env = data->s_env;
// 	separator = ft_strchr(str, '=');
// 	if (!separator)
// 		var_len = ft_strlen(str);
// 	else
// 		var_len = separator - str;
// 	key = malloc(sizeof(char *) * var_len + 1);
// 	if (!key)
// 		critical_failure(data, "malloc failed\n");
// 	ft_memcpy(key, str, var_len);
// 	key[var_len] = '\0';
// 	while (env)
// 	{
// 		if (ft_strcmp(env->var, key) == 0)
// 		{
// 			if (!separator || *(separator + 1) == '\0')
// 				switch_values(data, env, NULL, 1);
// 			else
// 				switch_values(data, env, separator + 1,
//                  ft_strlen(separator + 1));
// 			i++;
// 			break ;
// 		}
// 		env = env->next;
// 	}
// 	while (s_env)
// 	{
// 		if (ft_strcmp(s_env->var, key) == 0)
// 		{
// 			if (!separator || *(separator + 1) == '\0')
// 				switch_values(data, s_env, NULL, 1);
// 			else
// 				switch_values(data, s_env, separator + 1,
//                  ft_strlen(separator + 1));
// 			i++;
// 			break ;
// 		}
// 		s_env = s_env->next;
// 	}
// 	free(key);
// 	if (i == 2)
// 		return (0);
// 	return (1);
// }
