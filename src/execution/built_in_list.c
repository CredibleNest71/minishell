/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:10:32 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/22 11:16:13 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

char	*put_str(char *s)
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
}

void	put_built_in(int index, t_bigshell *data)
{
	if (index == 0)
	{
		data->built_ins[index] = malloc(sizeof(char) * 7);
		data->built_ins[index] = "echo -n";
	}
	else if (index == 1)
	{
		data->built_ins[index] = malloc(sizeof(char) * 2);
		data->built_ins[index] = "cd";
	}
	else if (index == 2)
	{
		data->built_ins[index] = malloc(sizeof(char) * 3);
		data->built_ins[index] = "pwd";
	}
	else if (index == 3)
	{
		data->built_ins[index] = malloc(sizeof(char) * 6);
		data->built_ins[index] = "export";
	}
	else if (index == 4)
	{
		data->built_ins[index] = malloc(sizeof(char) * 5);
		data->built_ins[index] = "unset";
	}
	else if (index == 5)
	{
		data->built_ins[index] = malloc(sizeof(char) * 3);
		data->built_ins[index] = "env";
	}
	else if (index == 6)
	{
		data->built_ins[index] = malloc(sizeof(char) * 4);
		data->built_ins[index] = "exit";
	}
}

void	built_in_list(t_bigshell *data)
{
	int		i;

	i = 0;
	while (i < 7)
		put_built_in(i++, data);
	data->built_ins[i] = NULL;
}

void	builtin_exec(t_bigshell *data, int builtin_index)
{
	if (builtin_index == 0)
	{
		if (!data->commands->args)
			ft_echo(data->commands->args, 0);
		else if (ft_strncmp(data->commands->args->str, "-n", 2) == 0)
			ft_echo(data->commands->args, 1);
		else 
			ft_echo(data->commands->args, 0);
	}
	else if (builtin_index == 1)
		ft_cd(data);
	else if (builtin_index == 2)
		ft_pwd(data);
	else if (builtin_index == 3)
		ft_export(data);
	/*else if (builtin_index == 4)
		ft_unset();
	else if (builtin_index == 5)
		ft_env(data);
	else if (builtin_index == 6)
		ft_exit(); */
}

void	builtin_check_exec(t_bigshell *data, char *cmd)
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
			//printf("built in found"); //exec built-in
		}
		i++;
	}
	return ;
}

/* while (list[i])
{
	i++;
} */
