/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:04 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 19:25:49 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_pwd(t_bigshell *data, t_command *cmd)
{
	char	*cwd;

	if (cmd->args && cmd->args->str[0] == '-')
	{
		ft_putstr_fd("minishell: pwd: invalid option\n", 1);
		return (update_exit_stat(data, 2));
	}
	cwd = get_cwd(data);
	if (!cwd)
	{
		ft_putstr_fd("Current Working Directory Not Found\n", 1);
		return (update_exit_stat(data, 1));
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	return (free(cwd), update_exit_stat(data, 0));
}

/* void	ft_pwd(t_bigshell *data)
{
	char	*cwd;
	t_env	*tmp;

	tmp = data->env;
	cwd = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD", 3) == 0)
		{
			cwd = ft_strdup(tmp->value);
			if (!cwd)
				critical_failure(data, "pwd: strdup failed");
			break ;
		}
		tmp = tmp->next;
	}
	if (!cwd)
	{
		ft_putstr_fd("Current Working Directory Not Found\n", 1);
		return (update_exit_stat(data, 1));
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	return (free(cwd), update_exit_stat(data, 0));
} */
