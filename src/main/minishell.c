/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/06 16:00:58 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../minishell.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **env)
{
	t_bigshell	bigshell;
	char		*lineread;
	int			i;

	lineread = NULL;
	bigshell.env = env;
	bigshell.built_ins = built_in_list();
	i = 0;
		while (1)
	    {
		    lineread = readline("tinyshell: ");
		    bigshell.commands = parse(stdin);
			store_restore_fds(1); //will store stdin & stdout
			if (bigshell.num_cmd == 1)
			{
				if ((bigshell.id = fork()) == -1)
					fatal_error(&bigshell, 1);
				if (bigshell.id == 0)
					simple_exec(&bigshell);
			}
			else
			{
				while (i < bigshell.num_cmd)
				{
					if ((bigshell.id = fork()) == -1)
						fatal_error(&bigshell, 1);
					if (bigshell.id == 0)
						complex_exec(bigshell, i);	
					i++;
				}
			}
	    }
	    return (0);
}
