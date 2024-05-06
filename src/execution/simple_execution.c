/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/06 17:28:38 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "../../minishell.h"
#include "../main/sig.h"
#include <stdio.h>
#include <strings.h>

// needs to be a child bc execve will kill the process otherwise
//we 1st check if redir is needed. <input & <<heredoc are both stored in cmd->input
//therefore if im coming from heredoc it'll enter redir. If <<heredoc is the final
//file then ill try to access it. have to make tmpfile.txt accesible to redir()
//overwrite input->str? (stupid? probably) make new struct member char *heredoc_file?

void	simple_exec(t_bigshell *data)
{
	set_signals(3);
	close_unused_fds(data);
	data->exec->paths = NULL;
	data->exec->path = NULL;
	if (g_sig == SIGINT) //check for signal before executing any command. if yes, spit prompt again
			CRITICAL_FAILURE(data, "simple exec: SIGINT received");
	convert_env(data); //check this function env struct has changed
	data->exec->paths = find_and_split_path(data->mod_env);
	// if (!data->exec->paths)
	// 	exit_child(data, 1); //find &split failed
	data->exec->path = check_if_correct_path(data->exec->paths, data, data->commands->cmd->str);
	if (!data->exec->path)
	{
		printf("minishell: command '%s' not found\n", data->commands->cmd->str);
		exit_child(data, 127);
	}
	execve(data->exec->path, data->commands->args_exec, data->mod_env);
	if (data->exec->path[0] == '/' || data->exec->path[0] == '.')
	{
		printf("minishell: %s: No such file or directory\n", data->exec->path);
		exit_child(data, 127);
	}
	exit_child(data, 126);
}
