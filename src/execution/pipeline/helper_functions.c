/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:28 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/10 16:52:56 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	pipe_init(t_bigshell *data)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		critical_failure(data, "pipe_init: malloc fail");
	data->pipe = pipe;
}

void	restore_output(t_bigshell *data)
{
	if (dup2(data->std_out, 1) == -1)
		critical_failure(data, "restoring stdout: dup2 fail");
}

void	error_exit(t_bigshell *data, int status, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit_child(data, status);
}

void	wait_for_children(t_bigshell *data)
{
	t_command	*cmd;
	int			stat_loc;

	cmd = data->commands;
	stat_loc = get_exitcode(data);
	while (cmd)
	{
		waitpid(cmd->pid, &stat_loc, 0);
		if (WIFEXITED(stat_loc))
		{
			stat_loc = WEXITSTATUS(stat_loc);
			update_exit_stat(data, stat_loc);
		}
		if (WIFSIGNALED(stat_loc))
		{
			stat_loc = WTERMSIG(stat_loc);
			if (stat_loc == SIGINT || stat_loc == SIGQUIT)
				stat_loc += 128;
			update_exit_stat(data, stat_loc);
		}
		cmd = cmd->next;
	}
}
