/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:41:58 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/04 15:50:08 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdlib.h>

void	update_exit_stat(t_bigshell *data, int exit_code)
{
	t_env	*tmp;
	char	*code;

	tmp = data->env;
	code = ft_itoa(exit_code);
	if (!code)
		CRITICAL_FAILURE(data, "redir error: itoa failed");
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, "?", ft_strlen(tmp->var)))
		{
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			tmp->value = ft_strdup(code);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "redir error: couldn't reassign exit status to env");
			break ;
		}
		tmp = tmp->next;
	}
}

void	redir_error(t_bigshell *data, int exit_code, char *str)
{
	printf("%s\n", str);
	update_exit_stat(data, exit_code);
}

void	simple_error(t_bigshell *data, int exit_code)
{
	update_exit_stat(data, exit_code);
	data->simple_error = EXIT_FAILURE;
} //if im in a child process I exit, otherwisee nor
	//perror("MINISHELL FAILURE:");
	// ;
	//exit(data->exit_stat);

/* int	errorin_child(t_bigshell *data)
{
	
} */

void	CRITICAL_FAILURE(t_bigshell *data, char *str)
{
	if (str)
		printf("%s\n", str);
	free_struct(data);
	exit(1);
}
