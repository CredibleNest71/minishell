/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:10:32 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 15:32:56 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <stdlib.h>

int	builtin_allrounder(t_bigshell *data, t_command *current_command)
{
	int	result;

	if (!data->built_ins)
	{
		data->built_ins = (char **)malloc(sizeof(char *) * 8);
		built_in_list(data);
	}
	if (!current_command->cmd)
		return (EXIT_FAILURE);
	result = builtin_check_exec(data, current_command->cmd->str,
			current_command);
	return (result);
}

void	built_in_list(t_bigshell *data)
{
	int		i;

	i = -1;
	while (++i < 7)
		put_built_in(i, data);
	data->built_ins[i] = NULL;
}

void	builtin_exec(t_bigshell *data, int builtin_index, t_command *cmd)
{
	if (builtin_index == 0)
	{
		if (!cmd->args)
			ft_echo(data, cmd->args);
		else
			ft_echo(data, cmd->args);
	}
	else if (builtin_index == 1)
		ft_cd(data);
	else if (builtin_index == 2)
		ft_pwd(data, cmd);
	else if (builtin_index == 3)
		ft_export(data);
	else if (builtin_index == 4)
		ft_unset(data, cmd);
	else if (builtin_index == 5)
		ft_env(data);
	else if (builtin_index == 6)
		ft_exit(data, cmd);
}

int	builtin_check_exec(t_bigshell *data, char *cmd, t_command *command)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(cmd);
	while (data->built_ins[i] != NULL)
	{
		if (ft_strncmp(cmd, "echo", len + 1) == 0)
		{
			builtin_exec(data, 0, command);
			return (0);
		}
		else if (ft_strncmp(cmd, data->built_ins[i], len + 1) == 0)
		{
			builtin_exec(data, i, command);
			return (0);
		}
		i++;
	}
	return (1);
}

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
