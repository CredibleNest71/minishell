/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:10:32 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/12 15:42:33 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

/* char	*put_str(char *s) //do I even use this
{
	int		len;
	int		i;
	char	*str;

	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = -1;
	while (str[++i])
		str[i] = s[i];
	return (str);
} */

int	builtin_allrounder(t_bigshell *data)
{
	int	result;
	
	data->built_ins = (char **)malloc(sizeof(char *) * 8);
	built_in_list(data);
	result = builtin_check_exec(data, data->commands->cmd->str);
	return (result);
}

void	put_built_in(int index, t_bigshell *data)
{
	if (index == 0)
	{
		data->built_ins[index] = ft_strdup("echo -n");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for echo");
	}
	else if (index == 1)
	{
		data->built_ins[index] = ft_strdup("cd");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for cd");
	}
	else if (index == 2)
	{
		data->built_ins[index] = ft_strdup("pwd");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for pwd");
	}
	else if (index == 3)
	{
		data->built_ins[index] = ft_strdup("export");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for export");
	}
	else if (index == 4)
	{
		data->built_ins[index] = ft_strdup("unset");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for unset");
	}
	else if (index == 5)
	{
		data->built_ins[index] = ft_strdup("env");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for env");
	}
	else if (index == 6)
	{
		data->built_ins[index] = ft_strdup("exit");
		if (!data->built_ins[index])
			CRITICAL_FAILURE(data, "built_in_list: strdup failed for exit");
	}
}

void	built_in_list(t_bigshell *data)
{
	int		i;

	i = -1;
	while (++i < 7)
		put_built_in(i, data);
	data->built_ins[i] = NULL;
}

void	builtin_exec(t_bigshell *data, int builtin_index)
{
	if (builtin_index == 0)
	{
		if (!data->commands->args)
			ft_echo(data->commands->args);
		else 
			ft_echo(data->commands->args);
	}
	else if (builtin_index == 1)
		ft_cd(data);
	else if (builtin_index == 2)
		ft_pwd(data);
	else if (builtin_index == 3)
		ft_export(data);
	else if (builtin_index == 4)
		ft_unset(data);
	else if (builtin_index == 5)
		ft_env(data);
	else if (builtin_index == 6)
		ft_exit(data);
}

int	builtin_check_exec(t_bigshell *data, char *cmd)
{
	int		len;
	int		i;
	
	i = 0;
	len = ft_strlen(cmd);
	while (data->built_ins[i] != NULL)
	{
		if (ft_strncmp(cmd, data->built_ins[i], len) == 0)
		{
			builtin_exec(data, i);
			return(0);
		}
		i++;
	}
	return(1);
}

/* while (list[i])
{
	i++;
} */
