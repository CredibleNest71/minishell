/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:41:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/06 12:51:09 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	simple_error(t_bigshell *main, int exit_code)
{
	main->exit_stat = exit_code;
	perror("MINISHELL FAILURE:");
	exit(main->exit_stat); //exit wrong f(x), go back to while(1)loop& finish it to print new prompt
	//exit is not wrong, simple execution needs to happen in a child, otherwise execve will kill main process
}

void	fatal_error(t_bigshell *main, int exit_code)
{
	main->exit_stat = exit_code;
	exit(1);
}
