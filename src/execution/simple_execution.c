/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/11 12:11:04 by ischmutz         ###   ########.fr       */
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
	char	**paths;
	char	*correct_path;
	
	paths = NULL;
	correct_path = NULL;
	if (g_sig.sigint) //check for signal before executing any command. if yes, spit prompt again
			exit_child(data, 130); //SIGINT received
	convert_env(data); //check this function env struct has changed
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		exit_child(data, 1); //find &split failed
		//printf("find&split failed\n"); //shit has been allocated
	correct_path = check_if_correct_path(paths, data, data->commands->cmd->str);
	if (!correct_path)
	{
		printf("minishell: command '%s' not found\n", data->commands->cmd->str);
		exit_child(data, 127);
	}
	execve(correct_path, data->commands->args_exec, data->mod_env);
	free(correct_path);
	free(paths);
	exit_child(data, 126);
	//free paths & args_exec
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