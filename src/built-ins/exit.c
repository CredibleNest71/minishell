/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:02:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/06 12:39:47 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_exitcode(t_bigshell *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "?", ft_strlen(tmp->var)) == 0)
			return (ft_atoi(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

void	update_exit_stat(t_bigshell *data, int exit_code) //gotta free code (LEAK)
{
	t_env	*tmp;
	char	*code;

	tmp = data->env;
	code = ft_itoa(exit_code);
	if (!code)
		CRITICAL_FAILURE(data, "redir error: itoa failed");
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, "?", ft_strlen(tmp->var)))
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			tmp->value = ft_strdup(code);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "redir error: couldn't reassign exit status to env");
			break ;
		}
		tmp = tmp->next;
	}
	free(code);
}

/* int	check_for_longlong(char *str)
{
	if (ft_strlen(str) > 20)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return (0);
	}
	return (1);
} */

int	check_numeric(char *str)
{
	int	i;

	i = 0;
	//check_for_longlong(str);
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

//update: closing stored original stdin stdout in free struct
void	ft_exit(t_bigshell *data, t_command *cmd)
{
	int	exitcode = 0;
	
	if (cmd->args && check_numeric(cmd->args->str) && cmd->arg_num > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (update_exit_stat(data, 1));
	}
	if (cmd->args && !check_numeric(cmd->args->str))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		return (update_exit_stat(data, 2), free_struct(data), exit(2));
	}
	if (cmd->arg_num == 1)
	{
		update_exit_stat(data, (unsigned int)ft_atoi(cmd->args->str) % 256);
	}
	exitcode = get_exitcode(data);
	free_struct(data);
	//ft_putstr_fd("exit\n", 2);
	exit(exitcode);
}
