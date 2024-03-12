/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/12 14:57:09 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>
#include <string.h>
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
char	*delete_tail(char *full_path)
{
	char	*end; 
	//int		diff;
	
	if (!full_path)
		return (NULL);
	end = ft_strrchr(full_path, '/');
	if (!end)
		return (NULL);
	*end = 0;
	// diff = end - full_path;
	// full_path[diff] = 0;
	return (full_path);
	// int		i;
	// int		j;
	// int		len;
	// char	*mod_path;
	
	// i = 0;
	// j = 0;
	// len = ft_strlen(full_path);
	// while (full_path[i])
	// 	i++;
	// while (full_path[i] && full_path[i] != '/')
	// {
	// 	i--;
	// 	j++;
	// }
	// len -= j;
	// i = -1;
	// mod_path = malloc(sizeof(char) * len);
	// if (!mod_path)
	// 	fatal_error(data, 1);
	// while (full_path[++i] && i < len)
	// 	mod_path[i] = full_path[i];
	// mod_path[i] = '\0';
	// printf("mod: %s\n", mod_path);
	// return (mod_path);
}

//this function will change the contents of data->env at pos PWD= 
void	overwrite_pwd(t_bigshell *data, char *to_join)
{
	t_env	*tmp;
	char	*new_str;

	tmp = data->env;
	new_str = ft_strjoin("PWD=", to_join);
	if (!new_str)
		fatal_error(data, 1);
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PWD", 3) == 0)
		{
			free(tmp->str);
			tmp->str = NULL;
			tmp->str = ft_strdup(new_str);
			if (!tmp->str)
				fatal_error(data, 1);
			break ;
		}
		tmp = tmp->next;
	}
}

void	connect_path(t_bigshell *data, char *to_join)
{
	t_env	*tmp;
	//char	*str;
	char	*new_str;
	//int		i;

	//i = -1;
	tmp = data->env;
	new_str = ft_strjoin("/", to_join);
	/* new_str = malloc(sizeof(char) * ft_strlen(str));
	while (++i < ft_strlen(str))
		new_str[i] = str[i]; */
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "PWD=", 4) == 0)
		{
			new_str = ft_strjoin(tmp->str, new_str);
			free(tmp->str);
			tmp->str = NULL;
			tmp->str = ft_strdup(new_str);
			if (!tmp->str)
				fatal_error(data, 1);
			break ;		
		}
		tmp = tmp->next;
	}
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
	if (data->commands->args && ft_strncmp(data->commands->args->str, "..", 2) == 0)
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
			getcwd(cwd, buffer_size);
			if (!cwd && errno == ERANGE)
			{
				//simple_error(data, 1); //perror: unable to get current dir
				free(cwd);
				cwd = NULL;
				buffer_size += BUFFER_INCREMENT;
			}
			if (!cwd && errno != ERANGE)
			{
				free(cwd);
				cwd = NULL;
				simple_error(data, 1); // built-in fails: unable to get current directory
			}
		}
		mod_cwd = delete_tail(cwd);
		//printf("mod_cwd: %s\n", mod_cwd);
		overwrite_pwd(data, mod_cwd);
		chdir (mod_cwd);
		free(cwd);
		return ;
	}
	if (!data->commands->args || ft_strncmp(data->commands->args->str, "~", 1) == 0)
	{
		path = getenv("HOME");
		//printf("path: %s\n", path);
		overwrite_pwd(data, path);
	}
	else
	{
		path = data->commands->args->str;
		delete_tail(path);
		connect_path(data, path);
	}
	// else (data->commands->args[0])
	//	path = data->commands->args[0]->str;
	//printf("%s\n", path);
	if (chdir(path) == -1) //this is probably fuckin unnecessary at this point
		printf("fucking chdir\n");
		//simple_error(data, 1);
		//perror("cd failure:");
	/*char	*test;
	test = malloc(sizeof(char) * BUFFER);
	test = getcwd(test, BUFFER);
	//printf("%s\n", test);*/
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