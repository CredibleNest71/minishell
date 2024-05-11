/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 12:32:50 by mresch           ###   ########.fr       */
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

int	mainloop(t_bigshell *data, char *lineread)
{
	int	in;

	while (1)
	{
		in = get_input(data, lineread);
		if (in == -1)
			return (1);
		else if (!in)
			continue ;
		set_signals(1);
		store_restore_fds(data, 1);
		ft_heredoc(data);
		if (g_sig == SIGINT)
			continue ;
		if (!execute(data))
			continue ;
		store_restore_fds(data, 2);
		free(lineread);
		close_unused_fds(data);
		tmpfile_cleanup(data);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_bigshell			data;
	char				*lineread;

	if (argc && argv)
		argv[argc - 1] = argv[argc - 1];
	init_all(&data, env);
	lineread = NULL;
	mainloop(&data, lineread);
	return (exitcode_and_freeshell(&data));
}
