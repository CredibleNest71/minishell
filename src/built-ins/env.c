/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:01:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/15 17:23:53 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//what should happen if env -i is run?
//how does env work with args?

//tf is this ft for
/* void	add_env_variable(t_bigshell *data)
{
	//if we make data->env a linked list maybe its better
	int	i;

	i = 0;
	while (data->og_env[i])
		i++;
	data->og_env = malloc((i + 1) * sizeof(char *)); //protect
	data->og_env[i++] = data->export_var;
	data->og_env[i] = NULL;
	data->exit_stat = 0;
	//exit(data->exit_stat);
	return ;
} */

//env should be a linked list and if export is used, add variable randomly
// env with no options or arguments --> returning prompt
void	ft_env(t_bigshell *data)
{
	t_env	*tmp;

	tmp = data->env;
	if (!tmp)
		return ;
	if (data->commands->arg_num == 0)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->var, "?", ft_strlen(tmp->var)) == 0)
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
		return ;
	}
	return ;
}
