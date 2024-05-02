/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/02 15:14:41 by ischmutz         ###   ########.fr       */
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

// static int	reset_data(t_bigshell *data)
// {
// 	data->commands = NULL;
// 	data->mod_cwd = NULL;
// 	data->mod_env = NULL;
// 	data->built_ins = NULL;
// 	data->pipe = NULL;
// 	data->s_env = NULL;
// 	data->pipe = NULL;
// 	data->heredoc = NULL;
// 	bzero(data, sizeof(t_bigshell));
// 	return (0);
// }

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
			return (/*write(1, "exit\n", 5), */get_exitcode(&data), free_struct(&data), 0);
		add_history(lineread);
		data.commands = parse(lineread, &data);
		//print_cmds(data.commands, &data);
		set_signals(1);
		if (!data.commands)
			continue ;
		store_restore_fds(&data, 1);
		// if (heredoc_finder(&data) == 0)
		// 	ft_heredoc(&data);
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
			if (builtin_allrounder(&data) == 0)
			{
				update_exit_stat(&data, 0);
				store_restore_fds(&data, 2);
				tmpfile_cleanup(&data);
				continue ;
			}
			data.commands->pid = fork();
			if (data.commands->pid == -1)
				CRITICAL_FAILURE(&data, "main: fork failed");
			if (data.commands->pid == 0)
				simple_exec(&data);
			//wait(NULL);
			wait_for_children(&data); //use specific children waiting ft here for correct exit code
		}
		else if (data.commands->next)
		{
			complex_exec(&data);
		}
		//printf("am I here?\n"); //debugging printf
		store_restore_fds(&data, 2);
		free(lineread);
		close_unused_fds(&data);
		tmpfile_cleanup(&data);
	}
	free_struct(&data);
}
