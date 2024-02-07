/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/07 18:16:09 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//-n: this option is used to omit echoing trailing newline.

void	ft_echo(t_token **args, int option) //maybe check if args is empty
{
	printf("hello\n");
	int i = 0;
	if (option == 1)
	{
		while (args[++i] != NULL)
			ft_putstr_fd(args[i]->str, 2);
	}
	else
	{
		while(args[i] != NULL)
			ft_putstr_fd(args[i++]->str, 2);
		ft_putchar_fd('\n', 2);
	}
	exit(0);
}
