/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainextra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:27:06 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 12:35:07 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parser/parse.h"
#include "sig.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		++i;
	}
	return (s1[i] - s2[i]);
}

int	exitcode_and_freeshell(t_bigshell *data)
{
	int	exitcode;

	exitcode = get_exitcode(data);
	free_struct(data);
	return (exitcode);
}

int	remove_cmd_list_from_data(t_bigshell *data)
{
	if (data->commands)
	{
		delete_command_list(data->commands);
		data->commands = NULL;
	}
	if (data->heredoc)
	{
		delete_token_list(data->heredoc);
		data->heredoc = NULL;
	}
	return (0);
}

void	exec_init(t_bigshell *data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		critical_failure(data, "exec_init: malloc fail");
	exec->path = NULL;
	exec->paths = NULL;
	data->exec = exec;
}

void	fd_init(t_bigshell *data)
{
	data->std_in = -1;
	data->std_out = -1;
	data->fd_in = -1;
	data->fd_out = -1;
}
