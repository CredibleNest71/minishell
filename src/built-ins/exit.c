/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:02:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/18 12:45:42 by ischmutz         ###   ########.fr       */
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

//update: closing stored original stdin stdout in free struct
void	ft_exit(t_bigshell *data, t_command *cmd)
{
	int	exitcode;
	
	if (cmd->arg_num > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exitcode = get_exitcode(data);
		free_struct(data);
		exit(exitcode);
	}
	if (cmd->arg_num == 1)
		update_exit_stat(data, ft_atoi(cmd->args->str));
	exitcode = get_exitcode(data);
	free_struct(data);
	//ft_putstr_fd("exit\n", 2);
	exit(exitcode);
}
