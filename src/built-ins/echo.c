/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/14 12:11:13 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-n: this option is used to omit echoing trailing newline.
//maybe check if args is empty
void	ft_echo(t_token *args, int option)
{
	int	count;

	count = 0;
	while (args)
	{
		if (count++)
			ft_putchar_fd(' ', 1);
		if (strncmp(args->str, "-n", 3))
			ft_putstr_fd(args->str, 1);
		args = args->next;
	}
	if (!option)
		ft_putchar_fd('\n', 1);
	return ;
}
