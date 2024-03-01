/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/01 11:27:40 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-n: this option is used to omit echoing trailing newline.

void	ft_echo(t_token *args, int option) //maybe check if args is empty
{
	if (option == 1)
	{
		if (!args)
			return ;
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
	return ;
}
