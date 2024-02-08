/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/08 17:05:40 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-n: this option is used to omit echoing trailing newline.

void	ft_echo(t_token **args, int option) //maybe check if args is empty
{
	int i = 0;
	if (!args || !args)
		return ;
	if (option == 1)
	{
		while (args[++i] != NULL)
			ft_putstr_fd(args[i]->str, 1);
	}
	else
	{
		while(args[i] != NULL)
			ft_putstr_fd(args[i++]->str, 1);
		ft_putchar_fd('\n', 1);
	}
	exit(0);
}
