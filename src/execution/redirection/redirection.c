/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:59:11 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/10 17:55:45 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	redir_input(t_bigshell *data, int in_fd)
{
	if (in_fd == -1)
		return (redir_error(data, 1, "redir.c: open failed"), EXIT_FAILURE);
	if (dup2(in_fd, 0) == -1)
		return (redir_error(data, 1, "redir.c: dup2 failed"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_redir_input(t_bigshell *data, t_command *cmd, t_token *input)
{
	while (input)
	{
		if (!input->next && input->type == (enum type)HEREDOC && cmd->cmd)
		{
			if (check_file(data, cmd->tmpfile, 0) != 0)
				return (EXIT_FAILURE);
			data->fd_in = open(cmd->tmpfile, O_RDONLY);
		}
		else if (input->type != (enum type)HEREDOC)
		{
			if (check_file(data, input->str, 0) != 0)
				return (EXIT_FAILURE);
			data->fd_in = open(input->str, O_RDONLY);
		}
		if (!input->next)
			break ;
		else
		{
			if (data->fd_in != -1 && close(data->fd_in) == -1)
				return (redir_error(data, 1, "redir.c: open/close failed"),
					EXIT_FAILURE);
			input = input->next;
		}
	}
	return (redir_input(data, data->fd_in));
}

static int	check_redir_output(t_bigshell *data, t_token *out)
{
	while (out)
	{
		if (out->type == (enum type)APP)
			data->fd_out = open(out->str, O_CREAT | O_APPEND | O_WRONLY, 00644);
		else
			data->fd_out = open(out->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		if (check_file(data, out->str, 1) != 0)
			return (EXIT_FAILURE);
		if (data->fd_out == -1)
			return (update_exit_stat(data, 1), ft_putstr_fd("minishell: \
						No such file or directory\n", 2), EXIT_FAILURE);
		if (!out->next)
			break ;
		if (out->next)
		{
			if (data->fd_out != -1 && close(data->fd_out) == -1)
				return (redir_error(data, 1, "redir.c:137 close failed"),
					EXIT_FAILURE);
			out = out->next;
		}
	}
	if ((dup2(data->fd_out, 1)) == -1)
		return (redir_error(data, 1, "fd_out: dup2 failed2"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redir(t_command *command, t_bigshell *data)
{
	t_token		*in;
	t_token		*out;

	in = command->input;
	out = command->output;
	if (in)
	{
		if (!command->cmd && data->heredoc)
			return (EXIT_FAILURE);
		if (check_redir_input(data, command, in) != 0)
			return (EXIT_FAILURE);
	}
	if (out)
	{
		if (check_redir_output(data, out) != 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
