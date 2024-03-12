/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:04 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/12 11:20:18 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_pwd(t_bigshell *data)
// {
// 	char	*cwd;

// 	cwd = getenv("PWD");
// 	if (!cwd)
// 	{
// 		ft_putstr_fd("Current Working Directory Not Found", 1);
// 		data->exit_stat = 1;
// 		exit(data->exit_stat);
// 	}
// 	ft_putstr_fd(cwd, 1);
// 	ft_putchar_fd('\n', 1);
// 	return ;
// }

void	ft_pwd(t_bigshell *data)
{
	char	*cwd;
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PWD", 3))
		{
			cwd = tmp->str;
			break ;
		}
		tmp = tmp->next;
	}
	if (!cwd)
	{
		ft_putstr_fd("Current Working Directory Not Found", 1);
		data->exit_stat = 1;
		return ;
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	return ;
}
