/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:54:30 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/21 19:44:56 by a                ###   ########.fr       */
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

/* void	check_input_file(t_bigshell *data, char *file)
{
	int	permission;

	permission = access(file, F_OK);
	if (permission == -1)
		simple_error(data, 1); //wrong file permission whats exit code?
	permission = access(file, R_OK);
	if (permission == -1)
		simple_error(data, 1);
} */

void	simple_exec(t_bigshell *data)
{
	char	**paths;
	char	*correct_path;
	
	convert_env(data); //check this function env struct has changed
	paths = find_and_split_path(data->mod_env);
	if (!paths)
		printf("find&split failed\n"); //shit has been allocated
	correct_path = check_if_correct_path(paths, data, data->commands->cmd->str);
	if (!correct_path)
		printf("correct path failed\n"); // do smt probably
	execve(correct_path, data->commands->args_exec, data->mod_env);
	printf("hello2\n");
	free(correct_path);
	//free paths & args_exec
	printf("execve failed\n");
	//protect execve
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