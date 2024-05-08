/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:41:31 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/08 19:42:31 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//Functions present in this file:
// -> check_if_sorted
// -> switch_nodes
// -> sort_env -> sorts s_env alphabetically

//checks the first letter of the var name
int	check_if_sorted(t_env *current)
{
	if (ft_strncmp(current->var, current->next->var, 1) > 0)
		return (1);
	else
		return (0);
}

//switches the contents of the node
void	switch_nodes(t_env *current)
{
	char	*tmp_var;
	char	*tmp_value;

	tmp_var = current->var;
	tmp_value = current->value;
	current->var = current->next->var;
	current->value = current->next->value;
	current->next->var = tmp_var;
	current->next->value = tmp_value;
}

//sorts s_env alphabetically
void	sort_env(t_bigshell *data)
{
	t_env	*env_i;
	t_env	*env_j;

	env_i = data->s_env;
	while (env_i->next)
	{
		env_j = data->s_env;
		while (env_j->next)
		{
			if (check_if_sorted(env_j) == 1)
				switch_nodes(env_j);
			env_j = env_j->next;
		}
		env_i = env_i->next;
	}
}
