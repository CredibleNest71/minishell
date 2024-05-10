/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:00:13 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/10 16:02:07 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	store_restore_fds(t_bigshell *data, int mode)
{
	if (mode == 1)
	{
		data->std_in = dup(0);
		if (data->std_in == -1)
			critical_failure(data, "dup_stdin dup fail");
		data->std_out = dup(1);
		if (data->std_out == -1)
			critical_failure(data, "dup_stdout dup fail");
	}
	else if (mode == 2)
	{
		if ((dup2(data->std_in, 0)) == -1)
			critical_failure(data, "dup_stdin dup2 fail");
		if ((dup2(data->std_out, 1)) == -1)
			critical_failure(data, "dup_stdout dup2 fail");
		if (close(data->std_in) == -1 || close(data->std_out) == -1)
			critical_failure(data, "close std_in/std_out fail");
		data->std_in = -1;
		data->std_out = -1;
	}
}

/* printf("minishell: %s: No such file or directory\n", file);
//check later with mo about file beig void* && probably exit as well
data->exit_stat = 1; //$? --> 1: command not found */
int	check_file(t_bigshell *data, const char *file, int mode)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1 && mode == 0)
		return (redir_error(data, 1,
				"minishell: No such file or directory"), EXIT_FAILURE);
	else if (permission == -1 && mode == 1)
		return (EXIT_SUCCESS);
	if (mode == 0)
	{
		if (access(file, R_OK) == -1)
			return (redir_error(data, 1,
					"minishell: Permission denied"), EXIT_FAILURE);
	}
	else if (mode == 1)
	{
		if (access(file, W_OK) == -1)
			return (redir_error(data, 1,
					"minishell: Permission denied"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
