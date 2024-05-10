/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:19:41 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/10 16:50:55 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	close_read(t_bigshell *data)
{
	if (data->pipe->read)
	{
		if (close(data->pipe->read) == -1)
		{
			perror("close pipe read in child:");
			return (-1);
		}
		data->pipe->read = -1;
	}
	return (0);
}

int	close_write(t_bigshell *data)
{
	if (data->pipe->write)
	{
		if (close(data->pipe->write) == -1)
		{
			perror("close pipe write in child:");
			return (-1);
		}
		data->pipe->write = -1;
	}
	return (0);
}

int	close_pipe(t_bigshell *data, int mode)
{
	if (mode == 1)
		return(close_read(data));
	if (mode == 2)
		return(close_write(data));
	if (mode == 3)
	{
		if (close_read(data) == -1 || close_write(data) == -1)
			return (-1);
	}
	return (0);
}

void	close_redir_fds(t_bigshell *data)
{
	if (data->fd_in != -1)
	{
		if (close(data->fd_in) == -1)
			perror("close fd_in in child:");
		data->fd_in = -1;
	}
	if (data->fd_out != -1)
	{
		if (close(data->fd_out) == -1)
			perror("close fd_out in child:");
		data->fd_out = -1;
	}
}

void	close_std_fds(t_bigshell *data)
{
	if (data->std_in != -1)
	{
		if (close(data->std_in) == -1)
			perror("close std_in in child:");
		data->std_in = -1;
	}
	if (data->std_out != -1)
	{
		if (close(data->std_out) == -1)
			perror("close std_out in child:");
		data->std_out = -1;
	}
}

void	close_redir_fds_in_child(t_bigshell *data)
{
	close_redir_fds(data);
	close_std_fds(data);
}

// void	close_redir_fds_in_child(t_bigshell *data, int mode)
// {
// 	if (mode == 1)
// 		close_redir_fds(data);
// 	if (mode == 2)
// 		close_std_fds(data);
// }
