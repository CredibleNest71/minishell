/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/03 16:44:45 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include "../parser/parse.h"
#include "sig.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int	find(t_bigshell *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (strcmp(tmp->var, "?") == 0)
			return (ft_atoi(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

t_sig	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_bigshell			data;

	//sig_init(&data, &handler);
	if (argc && argv) 
		argv[argc - 1] = argv[argc - 1];
	bzero(&data, sizeof(data));
	store_env(&data, env);
	char *lineread;
	lineread = NULL;
	pipe_init(&data);
	while (1)
	{
		set_signals(0);
		if (isatty(fileno(stdin)))
			lineread = readline("smellyshell: ");
		else
		{
			char	*line;
			line = get_next_line(fileno(stdin));
			lineread = ft_strtrim(line, "\n");
			free(line);
		}
		if (!lineread)
		{
			//free_struct(&data);
			return (write(1, "\n", 1), find(&data));
		}
		add_history(lineread);
		//printf("I work here\n");
		data.commands = parse(lineread, &data);
		if (!data.commands)
			continue ;
		//print_cmds(data.commands, &data);
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
		////printf("am I here?\n"); //debugging printf
		store_restore_fds(&data, 2);
	}
}
