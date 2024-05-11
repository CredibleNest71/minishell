/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 18:14:24 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 18:14:43 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
