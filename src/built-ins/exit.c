/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:02:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/18 11:04:41 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(t_bigshell *data)
{
	int	exitcode;
	
	exitcode = get_exitcode(data);
	//free everything
	close(data->std_in);
	close(data->std_out);
	free_struct(data);
	//printf("exit\n");
	exit(exitcode);
}
