/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 09:57:03 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/02 17:04:20 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int check_flag(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

//-n: this option is used to omit echoing trailing newline.
//maybe check if args is empty
void	ft_echo(t_token *args)
{
	int	count;
	int	flag;

	count = 0;
	if (!args )
	{
		ft_putchar_fd('\n', 1);
		return ;
	}
	flag = check_flag(args->str);
	if (flag)
		args = args->next;
	while (check_flag(args->str))
		args = args->next;
	while (args)
	{
		if (count++)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args->str, 1);
		args = args->next;
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return ;
}
