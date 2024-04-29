/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/29 15:31:37 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parse.h"
#include "../../minishell.h"
#include <stdio.h>
#include <strings.h>

// needs to be a child bc execve will kill the process otherwise
//we 1st check if redir is needed. <input & <<heredoc are both stored in cmd->input
//therefore if im coming from heredoc it'll enter redir. If <<heredoc is the final
//file then ill try to access it. have to make tmpfile.txt accesible to redir()
//overwrite input->str? (stupid? probably) make new struct member char *heredoc_file?

void	simple_exec(t_bigshell *data)
{
	// char	**paths;
	// char	*correct_path;
	
	data->exec->paths = NULL;
	data->exec->path = NULL;
	if (g_sig == SIGINT) //check for signal before executing any command. if yes, spit prompt again
			CRITICAL_FAILURE(data, "complex exec: SIGINT received");
	//dprintf(2, "segfault\n");
	convert_env(data); //check this function env struct has changed
	data->exec->paths = find_and_split_path(data->mod_env);
	if (!data->exec->paths)
		exit_child(data, 1); //find &split failed
		//printf("find&split failed\n"); //shit has been allocated
	data->exec->path = check_if_correct_path(data->exec->paths, data, data->commands->cmd->str);
	if (!data->exec->path)
	{
		printf("minishell: command '%s' not found\n", data->commands->cmd->str);
		exit_child(data, 127);
	}
	//printf("path executed:%s\n", data->exec->path);
	execve(data->exec->path, data->commands->args_exec, data->mod_env);
	exit_child(data, 126);
}

/* void print_env_list(t_bigshell *data)
{
    t_env *current = data->env;
    while (current != NULL)
    {
        printf("%s\n", current->str);
        current = current->next;
    }
} */