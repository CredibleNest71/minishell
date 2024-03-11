/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/11 17:07:23 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

//relative or absolute path
//if only cd was called, go to home directory
//update env after chdir gets executed

/*enum type {
	ARG = 0,
	PATH,
	SEP,
} typedef e_type;*/

//This function takes a full path as input and removes the last directory from it.
char	*delete_tail(t_bigshell *data, char *full_path)
{
	int		i;
	int		j;
	int		len;
	char	*mod_path;
	
	i = 0;
	j = 0;
	len = ft_strlen(full_path);
	while (full_path[i])
		i++;
	while (full_path[i] && full_path[i] != '/')
	{
		i--;
		j++;
	}
	len -= j;
	i = -1;
	mod_path = malloc(sizeof(char) * len);
	if (!mod_path)
		fatal_error(data, 1);
	while (full_path[++i] && i < len)
		mod_path[i] = full_path[i];
	mod_path[i] = '\0';
	return (mod_path);
}

//This function changes the current working directory based on
//the provided arguments.
void	ft_cd(t_bigshell *data)
{
	char	*path;
	char	*cwd; //somehow dynamically allocate this
	char	*mod_cwd;
	size_t	buffer_size;
	
	cwd = NULL;
	if (data->commands->arg_num > 1)
		simple_error(data, 1); //perror prints "success"? should be too many args
	if (ft_strncmp(data->commands->args->str, "..", 2) == 0)
	{
		buffer_size = BUFFER;
		while (1)
		{
			if (cwd)
				break ;
			cwd = malloc(sizeof(char) * buffer_size);
			if (!cwd)
			{
				free(cwd);
				fatal_error(data, 1); //malloc fails
			}
			cwd = getcwd(cwd, buffer_size);
			if (!cwd && errno == ERANGE)
			{
				//simple_error(data, 1); //perror: unable to get current dir
				free(cwd);
				buffer_size += BUFFER_INCREMENT;
			}
			if (!cwd && errno != ERANGE)
				simple_error(data, 1); // built-in fails: unable to get current directory
		}
		mod_cwd = delete_tail(data, cwd);
		chdir (mod_cwd);
		free(cwd);
		free(mod_cwd);
	}
	if (!data->commands->args || ft_strncmp(data->commands->args->str, "~", 1) == 0)
		path = getenv("HOME");
	else
		path = data->commands->args->str;
	// else (data->commands->args[0])
	//	path = data->commands->args[0]->str;
	if (chdir(path) == -1)
		simple_error(data, 1);
		//perror("cd failure:");
	return ;
}

/* void	ft_cd(t_bigshell *data, int index)
{
	char	*path;
	if (data->commands[index]->cmd->type == (e_type) PATH)
		path = data->commands[index]->cmd->str;
	else
		path = getenv("HOME");
	if (chdir(path) == -1)
		perror("cd failure:");
	exit (0);
} */