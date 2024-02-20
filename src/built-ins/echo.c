/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/13 14:30:54 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-n: this option is used to omit echoing trailing newline.

void	ft_echo(t_token *args, int option) //maybe check if args is empty
{
	if (option == 1)
	{
		if (!args)
			exit(0);
		while (args)
		{
			ft_putstr_fd(args->str, 1);
			args = args->next;	
		}
	}
	else
	{
		if (!args)
		{
			ft_putchar_fd('\n', 1);
			exit(0);
		}
		while(args)
		{
			ft_putstr_fd(args->str, 1);
			args = args->next;
		}
		ft_putchar_fd('\n', 1);
	}
	exit(0);
}
