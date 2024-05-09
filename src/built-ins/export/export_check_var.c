/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 14:21:34 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 15:08:16 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//Functions present in this file:
// -> check_var -> checks whether the variable name is a valid identifier
// -> var-exists -> checks whether the variable already exists in the environment

//extension of check var -> norminette
static int	check_var2(t_bigshell *data, char *var)
{
	int		i;

	i = 0;
	if (!(var[0] == '_' || (var[0] >= 'A' && var[0] <= 'Z') || \
		(var[0] >= 'a' && var[0] <= 'z')))
	{
		free(var);
		ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
		return (update_exit_stat(data, 1), 1);
	}
	while (var[++i])
	{
		if (!(var[i] == '_' || (var[i] >= '0' && var[i] <= '9') || \
		(var[i] >= 'A' && var[i] <= 'Z') || (var[i] >= 'a' && var[i] <= 'z')))
		{
			free(var);
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			return (update_exit_stat(data, 1), 1);
		}
	}
	free(var);
	return (0);
}

//checks whether the variable name is a valid identifier
int	check_var(t_bigshell *data, char *key)
{
	char	*end;
	char	*var;

	var = ft_strdup(key);
	if (!var)
		CRITICAL_FAILURE(data, "export: strdup failed");
	end = ft_strchr(var, '=');
	if (!end)
		return (free(var), update_exit_stat(data, 0), 1);
		//banned but exit status is 0 for tester??
	if (end)
		*end = 0;
	return (check_var2(data, var));
}
