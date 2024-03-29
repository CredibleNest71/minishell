/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/11 17:49:48 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../parser/parse.h"
#include "sig.h"
#include <stdio.h>
#include <unistd.h>

t_sig	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_bigshell			data;

	//sig_init(&data, &handler);
	if (argc && argv) 
		argv[argc - 1] = argv[argc - 1];
	bzero(&data, sizeof(data));
 	data.og_env = env;
	store_env(&data, env);
	char *lineread;
	lineread = NULL;
	pipe_init(&data);
	while (1)
	{
		//set_signals(0);
		lineread = readline("lovelyshell: ");
		if (!lineread)
			return (write(1, "\n", 1), 130);
		add_history(lineread);
		data.commands = parse(lineread, &data);
		if (!data.commands)
			continue ;
		print_cmds(data.commands, &data);
		store_restore_fds(&data, 1);
		if (heredoc_finder(&data) == 0)
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
				store_restore_fds(&data, 2);
				continue ;
			}
			data.commands->pid = fork();
			if (data.commands->pid == -1)
				CRITICAL_FAILURE(&data, "main: fork failed");
			if (data.commands->pid == 0)
				simple_exec(&data);
			wait(NULL);
		}
		else if (data.num_cmd > 1)
		{
				complex_exec(&data);
		}
		/* else if (data.num_cmd > 1)
		{
			while (i < data.num_cmd)
			{
				if ((data.id = fork()) == -1)
					CRITICAL_FAILURE(&data, "main: fork failed 2");
				if (data.id == 0)
					complex_exec(data, i);
				i++;
			}
		} */
		printf("am I here?\n");
		store_restore_fds(&data, 2);
	}
}
