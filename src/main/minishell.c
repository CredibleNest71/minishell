/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/01 10:24:03 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	t_bigshell	data;
	char		*lineread;
	int			i;

	lineread = NULL;
	data.og_env = env;
	data.built_ins = (char **)malloc(sizeof(char *) * 8);
	built_in_list(&data);
	i = 0;
		while (1)
	    {
		    lineread = readline("tinyshell: ");
		    data.commands = parse(stdin);
			store_restore_fds(1); //will store stdin & stdout
			if (data.num_cmd == 1)
			{
				if ((data.id = fork()) == -1)
					fatal_error(&data, 1);
				if (data.id == 0)
					simple_exec(&data);
			}
			else
			{
				while (i < data.num_cmd)
				{
					if ((data.id = fork()) == -1)
						fatal_error(&data, 1);
					if (data.id == 0)
						complex_exec(data, i);
					i++;
				}
			}
	    }
	    return (0);
}
