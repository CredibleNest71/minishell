/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:28 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 16:07:04 by ischmutz         ###   ########.fr       */
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
	int			status;
	int			last_sig;

	cmd = data->commands;
	last_sig = 0;
	while (cmd)
	{
		if (waitpid(cmd->pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				update_exit_stat(data, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
			{
				last_sig = WTERMSIG(status);
				update_exit_stat(data, 128 + last_sig);
			}
		}
		cmd = cmd->next;
	}
	if (last_sig == SIGINT)
		write(1, "\n", 1);
	else if (last_sig == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}
