/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:02:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/16 12:42:06 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_bigshell *data)
{
	int	exitcode;
	
	exitcode = get_exitcode(data);
	//free everything
	free_struct(data);
	//printf("exit\n");
	exit(exitcode);
}
