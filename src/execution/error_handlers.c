/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:41:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/06 18:26:21 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include <iterator>
#include <stdlib.h>

void	redir_error(t_bigshell *data, int exit_code, char *str)
{
	printf("%s\n", str);
	update_exit_stat(data, exit_code);
}

void	simple_error_message(t_bigshell *data, char *str, int exit_code)
{
	printf("%s\n", str);
	update_exit_stat(data, exit_code);
	data->simple_error = EXIT_FAILURE;
}

void	simple_error(t_bigshell *data, int exit_code)
{
	update_exit_stat(data, exit_code);
	data->simple_error = EXIT_FAILURE;
} //if im in a child process I exit, otherwisee nor
	//perror("MINISHELL FAILURE:");
	// ;
	//exit(data->exit_stat);

/* int	errorin_child(t_bigshell *data)
{
	
} */

void	exit_child(t_bigshell *data, int exit_stat)
{
	free_struct(data);
	update_exit_stat(data, exit_stat);
	if (g_sig)
		exit(128 + g_sig);
	exit (exit_stat);
}

void	CRITICAL_FAILURE(t_bigshell *data, char *str)
{
	if (str)
		printf("%s\n", str);
	free_struct(data);
	exit(1); //which exit code should I exit the minishell with?
}
