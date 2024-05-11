/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:35:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 15:20:10 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//Functions present in this file:
// -> make_copy -> creates s_env and sorts it
// -> print_env -> prints env when export no args is called

//creates the first node in sorted env ->norminette
static void	create_first_node_s_env(t_bigshell *data)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(data->env->var, "=");
	if (!tmp)
		critical_failure(data, "export: strjoin failed 1");
	tmp1 = ft_strjoin(tmp, data->env->value);
	free(tmp);
	if (!tmp1)
		critical_failure(data, "export: strjoin failed 2");
	data->s_env = create_node(data, tmp1);
	free(tmp1);
}

//copies updated env into s_env & then sorts it
void	make_copy(t_bigshell *data)
{
	t_env	*current;
	t_env	*current_env;
	char	*tmp;
	char	*tmp1;

	create_first_node_s_env(data);
	current = data->s_env;
	current_env = data->env->next;
	while (current_env)
	{
		tmp = ft_strjoin(current_env->var, "=");
		if (!tmp)
			critical_failure(data, "export: strjoin failed 3");
		tmp1 = ft_strjoin(tmp, current_env->value);
		free(tmp);
		if (!tmp1)
			critical_failure(data, "export: strjoin failed 4");
		current->next = create_node(data, tmp1);
		free(tmp1);
		current = current->next;
		current_env = current_env->next;
		data->reference_i++;
	}
	sort_env(data);
	return ;
}

//prints env when export no args is called
void	print_env(t_env *head)
{
	while (head)
	{
		if (ft_strncmp(head->var, "?", ft_strlen(head->var)) == 0
			|| ft_strncmp(head->var, "_", ft_strlen(head->var)) == 0)
		{
			head = head->next;
			continue ;
		}
		printf("declare -x ");
		printf("%s", head->var);
		if (!head->value)
			printf("=\"\"\n");
		if (head->value)
			printf("=%c%s%c\n", 34, head->value, 34);
		head = head->next;
	}
}
