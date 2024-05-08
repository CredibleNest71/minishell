/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/08 18:16:24 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "../../minishell.h"
#include "../main/sig.h"
#include <stdio.h>
#include <strings.h>

// needs to be a child bc execve will kill the process otherwise
//we 1st check if redir is needed. <input & <<heredoc are both stored in
//cmd->input therefore if im coming from heredoc it'll enter redir. If
//<<heredoc is the final file then ill try to access it. have to make
//tmpfile.txt accesible to redir() overwrite input->str? (stupid? probably)
//make new struct member char *heredoc_file?

void	simple_exec(t_bigshell *data)
{
	set_signals(3);
	close_unused_fds(data);
	data->exec->paths = NULL;
	data->exec->path = NULL;
	if (g_sig == SIGINT)
		CRITICAL_FAILURE(data, "simple exec: SIGINT received");
	convert_env(data);
	data->exec->paths = find_and_split_path(data->mod_env); //should it be exit_child?
	data->exec->path = check_if_correct_path(data->exec->paths, data, \
		data->commands->cmd->str);
	if (!data->exec->path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit_child(data, 127);
	}
	execve(data->exec->path, data->commands->args_exec, data->mod_env);
	if (data->exec->path[0] == '/' || data->exec->path[0] == '.')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		exit_child(data, 127);
	}
	exit_child(data, 126);
}
