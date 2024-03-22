/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:04 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/13 11:15:41 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_bigshell *data)
{
	char	*cwd;
	t_env	*tmp;

	tmp = data->env;
	cwd = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD=", 4) == 0)
		{
			//maybe protect in case PWD= is only 4char long
			cwd = ft_strdup(tmp->value);
			if (!cwd)
				CRITICAL_FAILURE(data, "pwd: strdup failed");
			break ;
		}
		tmp = tmp->next;
	}
	if (!cwd)
	{
		ft_putstr_fd("Current Working Directory Not Found\n", 1);
		data->exit_stat = 1;
		return ;
	}
	ft_putstr_fd(cwd, 1);
	ft_putchar_fd('\n', 1);
	return ;
}
