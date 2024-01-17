/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:21:04 by ischmutz          #+#    #+#             */
/*   Updated: 2024/01/17 15:53:33 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	ft_pwd()
{
	char	*cwd;

	cwd = getenv("PWD");
	if (!cwd)
		ft_putstr_fd("Current Working Directory Not Found", 1);
	ft_putstr_fd(cwd, 1);
}
