/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_close_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:30:47 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/10 16:31:02 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//Functions present in this file:
// -> open_heredoc_fd -> opens the tmpfile for the heredoc
//  -> norminette
// -> close_heredoc_fd -> closes the tmpfile for the heredoc & sets it to -1
//  -> norminette
// -> free_set_null -> frees mod_eof and returns NULL
//  -> norminette 

int	open_heredoc_fd(t_bigshell *data, t_command *cmd)
{
	int	fd;

	fd = 0;
	if (cmd->tmpfile)
	{
		fd = open(cmd->tmpfile, O_CREAT | O_TRUNC | O_RDWR, 00644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: heredoc.c: open failed\n", 2);
			update_exit_stat(data, 1);
			return (-1);
		}
	}
	return (fd);
}

void	close_heredoc_fd(int fd)
{
	if (fd)
	{
		if (close(fd) == -1)
			perror("heredoc.c: close heredoc");
		fd = -1;
	}
}

char	*free_set_null(char *mod_eof)
{
	if (mod_eof)
		free(mod_eof);
	return (NULL);
}
