/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tmpfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:20:50 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/10 18:51:10 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

//Functions present in this file:
// -> tmpfile_cleanup -> goes through the cmd list and unlinks the tmpfiles
// -> unlink_free_tmpfile -> unlinks and frees the tmpfile, if multiple
//  heredocs are present in a cmd
// -> create_unique_name -> creates a semi unique name for the tmpfile

int	tmpfile_cleanup(t_bigshell *data)
{
	t_command	*cmd;

	cmd = data->commands;
	while (cmd)
	{
		if (cmd->tmpfile)
		{
			if (unlink(cmd->tmpfile) == -1)
				simple_error(data, 1);
			free(cmd->tmpfile);
		}
		cmd = cmd->next;
	}
	return (0);
}

static char	*unlink_free_tmpfile(char *tmpfile)
{
	unlink(tmpfile);
	free(tmpfile);
	return (NULL);
}

char	*create_unique_name(t_bigshell *data, t_command *cmd, char *eof)
{
	char	*tmpfile;

	if (cmd->tmpfile)
		cmd->tmpfile = unlink_free_tmpfile(cmd->tmpfile);
	tmpfile = ft_strjoin("tmpfile", eof);
	if (!tmpfile)
		critical_failure(data, "heredoc.c: strjoin: malloc failed");
	return (tmpfile);
}
