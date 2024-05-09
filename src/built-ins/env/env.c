/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:01:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 18:56:47 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//env should be a linked list and if export is used, add variable randomly
// env with no options or arguments --> returning prompt
void	ft_env(t_bigshell *data)
{
	t_env	*tmp;

	tmp = data->env;
	if (!tmp)
		return (update_exit_stat(data, 1));
	if (data->commands->arg_num == 0)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->var, "?") == 0)
			{
				tmp = tmp->next;
				continue ;
			}
			printf("%s", tmp->var);
			if (!tmp->value)
				printf("\n");
			if (tmp->value)
				printf("=%s\n", tmp->value);
			tmp = tmp->next;
		}
		return (update_exit_stat(data, 0));
	}
	return (update_exit_stat(data, 1));
}
