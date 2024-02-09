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

void	simple_error(t_bigshell *data, int exit_code)
{
	data->exit_stat = exit_code;
	perror("MINISHELL FAILURE:");
	exit(data->exit_stat);
}

void	fatal_error(t_bigshell *data, int exit_code)
{
	data->exit_stat = exit_code;
	exit(data->exit_stat); //exit minishell? probably
}
