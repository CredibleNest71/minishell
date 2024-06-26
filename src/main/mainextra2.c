/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainextra2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 12:32:02 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 20:06:29 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parser/parse.h"
#include "sig.h"

int	just_do_the_thing(t_bigshell *data)
{
	if (data->commands->cmd)
	{
		data->commands->pid = fork();
		if (data->commands->pid == -1)
			critical_failure(data, "main: fork failed");
		if (data->commands->pid == 0)
			simple_exec(data);
		wait_for_children(data);
	}
	return (1);
}

int	execute(t_bigshell *data)
{
	if (data->commands->next)
		return (complex_exec(data), 1);
	if (data->commands->input || data->commands->output)
	{
		if (redir(data->commands, data))
		{
			store_restore_fds(data, 2);
			tmpfile_cleanup(data);
			return (0);
		}
	}
	if (!builtin_allrounder(data, data->commands))
	{
		store_restore_fds(data, 2);
		close_unused_fds(data);
		tmpfile_cleanup(data);
		return (0);
	}
	just_do_the_thing(data);
	return (1);
}

void	init_all(t_bigshell *data, char **env)
{
	bzero(data, sizeof(t_bigshell));
	pipe_init(data);
	exec_init(data);
	store_env(data, env);
}

int	get_input(t_bigshell *data, char *lineread)
{
	g_sig = 0;
	set_signals(0);
	fd_init(data);
	remove_cmd_list_from_data(data);
	lineread = readline("minitrap: ");
	if (g_sig == SIGINT)
		update_exit_stat(data, 130);
	if (!lineread)
		return (-1);
	add_history(lineread);
	data->commands = parse(lineread, data);
	free(lineread);
	if (!data->commands)
		return (0);
	else
		return (1);
}
