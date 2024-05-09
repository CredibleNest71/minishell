/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:08:01 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 19:25:49 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	put_built_in2(int index, t_bigshell *data)
{
	if (index == 4)
	{
		data->built_ins[index] = ft_strdup("unset");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for unset");
	}
	else if (index == 5)
	{
		data->built_ins[index] = ft_strdup("env");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for env");
	}
	else if (index == 6)
	{
		data->built_ins[index] = ft_strdup("exit");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for exit");
	}
}

void	put_built_in(int index, t_bigshell *data)
{
	if (index == 0)
	{
		data->built_ins[index] = ft_strdup("echo -n");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for echo");
	}
	else if (index == 1)
	{
		data->built_ins[index] = ft_strdup("cd");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for cd");
	}
	else if (index == 2)
	{
		data->built_ins[index] = ft_strdup("pwd");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for pwd");
	}
	else if (index == 3)
	{
		data->built_ins[index] = ft_strdup("export");
		if (!data->built_ins[index])
			critical_failure(data, "built_in_list: strdup failed for export");
	}
	put_built_in2(index, data);
}
