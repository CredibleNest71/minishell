/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/26 15:20:13 by ischmutz         ###   ########.fr       */
=======
/*   Updated: 2024/04/29 13:55:32 by mresch           ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../parser/parse.h"
#include "sig.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern int	g_sig;

static int	reset_data(t_bigshell *data)
{
	bzero(&data, sizeof(data));
	data->commands = NULL;
	data->mod_cwd = NULL;
	data->mod_env = NULL;
	data->built_ins = NULL;
	data->pipe = NULL;
	data->s_env = NULL;
	data->pipe = NULL;
	data->heredoc = NULL;
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_bigshell			data;

	if (argc && argv)
		argv[argc - 1] = argv[argc - 1];
	reset_data(&data);
	store_env(&data, env);
	char *lineread;
	lineread = NULL;
	pipe_init(&data);
	while (1)
	{
		if (data.commands)
			delete_command_list(data.commands);
		if (data.heredoc)
		{
			delete_token_list(data.heredoc);
			data.heredoc = NULL;
		}
		set_signals(0);
		if (isatty(fileno(stdin)))
			lineread = readline("smellyshell: ");
		//else
		//{
		//	char	*line;
		//	line = get_next_line(fileno(stdin));
		//	lineread = ft_strtrim(line, "\n");
		//	free(line);
		//}
		if (!lineread)
			return (/*write(1, "exit\n", 5), */get_exitcode(&data));
		add_history(lineread);
		//printf("I work here\n");
		data.commands = parse(lineread, &data);
		print_cmds(data.commands, &data);
		set_signals(1);
		if (!data.commands)
			continue ;
		store_restore_fds(&data, 1);
		// if (heredoc_finder(&data) == 0)
		// 	ft_heredoc(&data);
		if (data.heredoc)
			ft_heredoc(&data);
		if (data.commands->input || data.commands->output)
		{
			if (redir(data.commands, &data))
			{
				store_restore_fds(&data, 2);
				continue ;
			}
		}
		if (data.num_cmd == 1)
		{
			if (builtin_allrounder(&data) == 0)
			{
				update_exit_stat(&data, 0);
				store_restore_fds(&data, 2);
				continue ;
			}
			data.commands->pid = fork();
			if (data.commands->pid == -1)
				CRITICAL_FAILURE(&data, "main: fork failed");
			if (data.commands->pid == 0)
				simple_exec(&data);
			wait(NULL);
			//wait_for_children(&data); //use specific children waiting ft here for correct exit code
		}
		else if (data.num_cmd > 1)
		{
				complex_exec(&data);
		}
		//printf("am I here?\n"); //debugging printf
		store_restore_fds(&data, 2);
		free(lineread);
		unlink("tmpfile.txt");
	}
	free_struct(&data);
}
