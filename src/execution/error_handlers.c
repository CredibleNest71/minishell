/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:41:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/09 10:19:24 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

void	redir_error(t_bigshell *data, int exit_code, char *str)
{
	printf("%s\n", str);
	data->exit_stat = exit_code;
}

void	simple_error(t_bigshell *data, int exit_code)
{
	data->exit_stat = exit_code;
	data->simple_error = EXIT_FAILURE;
	//perror("MINISHELL FAILURE:");
	// ;
	//exit(data->exit_stat);
} //if im in a child process I exit, otherwisee nor

void	CRITICAL_FAILURE(t_bigshell *data, char *str)
{
	if (str)
		printf("%s\n", str);
	free_struct(data);
	exit(1);
}
