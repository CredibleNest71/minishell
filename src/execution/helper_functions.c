/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:04:24 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/28 10:36:11 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//frees the node_to_delete in unset
void	free_single_node(t_bigshell *data, t_env **node)
{
	free((*node)->str);
	free(*node);
	data->exit_stat = 0;
}

//frees env & sorted env linked list (used in export & unset)
void	free_env(t_bigshell *data)
{
	t_env	*tmp;
	while (data->s_env)
	{
		tmp = data->s_env;
		data->s_env = data->s_env->next;
		free(tmp->str);
		free(tmp);
	}
	while (data->env)
	{
		tmp = data->env;
		data->env = data->env->next;
		free(tmp->str);
		free(tmp);
	}
}
