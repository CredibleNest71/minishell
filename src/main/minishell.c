/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/06 15:30:45 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../parser/parse.h"
#include "sig.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

extern int	g_sig;

int	exitcode_and_freeshell(t_bigshell *data)
{
	int	exitcode;

	exitcode = get_exitcode(data);
	free_struct(data);
	return (exitcode);
}

static int remove_cmd_list_from_data(t_bigshell *data)
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
		CRITICAL_FAILURE(data, "exec_init: malloc fail");
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

int	main(int argc, char **argv, char **env)
{
	t_bigshell			data;

	if (argc && argv)
		argv[argc - 1] = argv[argc - 1];
	bzero(&data, sizeof(data));
	pipe_init(&data);
	exec_init(&data);
	store_env(&data, env);
	char *lineread;
	lineread = NULL;
	while (1)
	{
		fd_init(&data);
		remove_cmd_list_from_data(&data);
		set_signals(0);
		if (isatty(fileno(stdin)))
			lineread = readline("minitrap: ");
		else
		{
			char	*line;
			line = get_next_line(fileno(stdin));
			lineread = ft_strtrim(line, "\n");
			free(line);
		}
		if (!lineread)
			return (/*write(1, "exit\n", 5), */exitcode_and_freeshell(&data));
		add_history(lineread);
		data.commands = parse(lineread, &data);
		print_cmds(data.commands, &data);
		if (!data.commands)
			continue ;
		set_signals(1);
		store_restore_fds(&data, 1);
		if (data.heredoc)
			ft_heredoc(&data);
		if (!data.commands->next)
		{
			if (data.commands->input || data.commands->output)
			{
				if (redir(data.commands, &data))
				{
					store_restore_fds(&data, 2);
					tmpfile_cleanup(&data);
					continue ;
				}
			}
			if (!builtin_allrounder(&data, data.commands))
			{
				store_restore_fds(&data, 2);
				close_unused_fds(&data);
				tmpfile_cleanup(&data);
				continue ;
			}
			if (data.commands->cmd)
			{
				data.commands->pid = fork();
				if (data.commands->pid == -1)
					CRITICAL_FAILURE(&data, "main: fork failed");
				if (data.commands->pid == 0)
					simple_exec(&data);
				wait_for_children(&data); //use specific children waiting ft here for correct exit code
			}
		}
		else if (data.commands->next)
		{
			complex_exec(&data);
		}
		store_restore_fds(&data, 2);
		free(lineread);
		close_unused_fds(&data);
		tmpfile_cleanup(&data);
	}
	return (exitcode_and_freeshell(&data));
}
