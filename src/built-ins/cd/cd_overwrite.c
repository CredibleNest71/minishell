/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_overwrite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:25:29 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 15:45:35 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <unistd.h>

//Functions present in this file:
// -> overwrite_s_env -> 
// -> overwrite_oldpwd -> 
// -> overwrite_pwd ->

//overwrites the values at pos env_var in s_env
void	overwrite_s_env(t_bigshell *data, char *env_var, char *str)
{
	t_env	*tmp;

	tmp = data->s_env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, env_var) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(str);
			if (!tmp->value)
				CRITICAL_FAILURE(data,
					"minishell: cd: strdup failed in overwrite_s_env");
			break ;
		}
		tmp = tmp->next;
	}
}

//overwrites the values at pos OLDPWD in env and s_env
void	overwrite_oldpwd(t_bigshell *data, char *oldpwd)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(oldpwd);
			if (!tmp->value)
				CRITICAL_FAILURE(data,
					"minishell: cd: strdup failed in overwrite_oldpwd");
			break ;
		}
		tmp = tmp->next;
	}
	overwrite_s_env(data, "OLDPWD", oldpwd);
}

//overwrites the values at pos PWD in env and s_env 
void	overwrite_pwd(t_bigshell *data, char *new_path)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->var, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(new_path);
			if (!tmp->value)
				CRITICAL_FAILURE(data,
					"minishell: cd: strdup failed in overwrite");
			break ;
		}
		tmp = tmp->next;
	}
	overwrite_s_env(data, "PWD", new_path);
}
