/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:29:54 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 19:31:26 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include "../../parser/parse.h"

//frees string arrays (like exec_args)
void	s_array_free(char **s_array)
{
	int	i;

	i = 0;
	if (!s_array)
		return ;
	while (s_array[i])
		free(s_array[i++]);
	free(s_array);
}

void	double_free_array(char **array1, char **array2)
{
	s_array_free(array1);
	s_array_free(array2);
}

//frees the node_to_delete in unset
//why do I update exit stat to 0?
void	free_single_node(t_bigshell *data, t_env **node)
{
	free((*node)->var);
	free((*node)->value);
	free(*node);
	update_exit_stat(data, 0);
}

//frees env & sorted env linked list (used in export & unset)
void	free_env(t_bigshell *data)
{
	t_env	*tmp;

	if (data->s_env)
	{
		while (data->s_env)
		{
			tmp = data->s_env;
			data->s_env = data->s_env->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
		}
	}
	if (data->env)
	{
		while (data->env)
		{
			tmp = data->env;
			data->env = data->env->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
		}
	}
}

void	free_builtin_list(t_bigshell *data)
{
	int	i;

	i = 0;
	if (data->built_ins)
	{
		while (data->built_ins[i])
			free(data->built_ins[i++]);
		free(data->built_ins);
	}
}
