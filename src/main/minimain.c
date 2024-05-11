/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 14:33:14 by ischmutz         ###   ########.fr       */
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

void	make_over(t_bigshell *data, char *lineread)
{
	store_restore_fds(data, 2);
	free(lineread);
	close_unused_fds(data);
	tmpfile_cleanup(data);
}

int	mainloop(t_bigshell *data, char *lineread)
{
	int	in;

	while (1)
	{
		in = get_input(data, lineread);
		if (in == -1)
			return (/*write(1, "exit\n", 6),*/ 1);
		else if (!in)
			continue ;
		store_restore_fds(data, 1);
		ft_heredoc(data);
		if (g_sig == SIGINT)
		{
			make_over(data, lineread);
			continue ;
		}
		set_signals(1);
		if (!execute(data))
			continue ;
		make_over(data, lineread);
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
