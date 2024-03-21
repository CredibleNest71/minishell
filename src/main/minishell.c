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
#include "../parser/parse.h"
#include <stdio.h>
#include <unistd.h>

t_sig	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_bigshell			data;
	struct sigaction	sa;

	if (argc && argv) 
		printf("\n");
	bzero(&data, sizeof(data));
 	data.og_env = env;
	store_env(&data, env);
	char *lineread;
	while (1)
	{
		lineread = readline("tinyshell: ");
		add_history(lineread);
		data.commands = parse(lineread, &data);
		if (!data.commands)
			continue ;
		print_cmds(data.commands, &data);
		store_restore_fds(1);
		if (heredoc_finder(&data) == 0)
			ft_heredoc(&data);
		if (data.commands->input || data.commands->output)
			redir(data.commands, &data);
		if (builtin_allrounder(&data) == 0)
			continue ;
		if (data.num_cmd == 1)
		{
			data.id = fork();
			printf("data id is %d \n", data.id);
			if (data.id == -1)
				fatal_error(&data, 1);
			if (data.id == 0)
				simple_exec(&data);
			wait(NULL);
		}
	}
}

