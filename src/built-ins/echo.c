/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/12 15:37:31 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-n: this option is used to omit echoing trailing newline.
//maybe check if args is empty
void	ft_echo(t_token *args, int option)
{
	int	count;

	count = 0;
	if (option == 1)
	{
		args = args->next;
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
			return ;
		}
		while(args)
		{
			if (count++)
				write(1, " ", 1);
			ft_putstr_fd(args->str, 1);
			args = args->next;
		}
		ft_putchar_fd('\n', 1);
	}
	return ;
}
