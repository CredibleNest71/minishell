/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/19 17:32:06 by ischmutz         ###   ########.fr       */
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
	// 	CRITICAL_FAILURE(data);
	// while (full_path[++i] && i < len)
	// 	mod_path[i] = full_path[i];
	// mod_path[i] = '\0';
	// printf("mod: %s\n", mod_path);
	// return (mod_path);
}

//this function will change the contents of data->env at pos PWD= 
void	overwrite_pwd(t_bigshell *data, char *new_path)
{
	t_env	*tmp;

	tmp = data->env; //should I also change them in s_env?
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD", ft_strlen(tmp->var)) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(new_path);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "minishell: cd: strdup failed in overwrite");
			break ;
		}
		tmp = tmp->next;
	}
}

char	*connect_path(t_bigshell *data, char *to_join)
{
	t_env	*tmp;
	//char	*str;
	char	*new_str;
	char	*tmp_value;
	//int		i;

	//i = -1;
	tmp = data->env;
	new_str = ft_strjoin("/", to_join);
	/* new_str = malloc(sizeof(char) * ft_strlen(str));
	while (++i < ft_strlen(str))
		new_str[i] = str[i]; */
	tmp_value = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD", 3) == 0)
		{
			new_str = ft_strjoin(tmp->value, new_str);
			tmp_value = malloc(sizeof(char) * ft_strlen(tmp->value));
			if (!tmp_value)
				CRITICAL_FAILURE(data, "cd: malloc failed");
			tmp_value = ft_strdup(tmp->value);
			if (!tmp_value)
				CRITICAL_FAILURE(data, "cd: strdup failed");
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(new_str);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "cd: strdup failed in path connecting");
			return (tmp_value);
			//break ;		
		}
		tmp = tmp->next;
	}
	return (tmp_value);
}

void	connect_ogpath(t_bigshell *data, char *og_path)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD", 3) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(og_path);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "cd: strdup failed in path connecting");
			break ;		
		}
		tmp = tmp->next;
	}
}

//This function changes the current working directory based on
//the provided arguments.
/* void	ft_cd(t_bigshell *data)
{
	char	*path;
	char	*og_path;
	char	*cwd;
	char	*mod_cwd;
	size_t	buffer_size;
	
	cwd = NULL;
	og_path = NULL;
	if (data->commands->arg_num > 1)
		simple_error(data, 1); //perror prints "success"? should be too many args
	if (data->commands->args && (ft_strncmp(data->commands->args->str, "..", 2) == 0 || ft_strncmp(data->commands->args->str, "../", 3) == 0))
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
				CRITICAL_FAILURE(data, "cd: malloc failed in ft_cd"); //malloc fails
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
		//printf("mod_cwd: %s\n", mod_cwd); //debugging printf?
		overwrite_pwd(data, mod_cwd);
		chdir (mod_cwd);
		free(cwd);
		if (ft_strlen(data->commands->args->str) > 3)
			
		return ;
	}
	if (!data->commands->args || ft_strncmp(data->commands->args->str, "~", ft_strlen(data->commands->args->str)) == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		overwrite_pwd(data, path);
	}
	else
	{
		path = data->commands->args->str;
		if (path[ft_strlen(path) - 1] == '/')
			path[ft_strlen(path) - 1] = 0;
		if (path[0] == '/')
		{
			if (chdir(path) == -1)
			{
				printf("minishell: cd: %s: No such file or directory\n", data->commands->args->str);
				simple_error(data, 1);
				return ;
			}
			overwrite_pwd(data, path);
			return ;
		}
		//delete_tail(path);
		og_path = connect_path(data, path);
		if (!og_path)
			printf("connect path failed\n");
		if (chdir(path) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", data->commands->args->str);
			simple_error(data, 1);
			connect_ogpath(data, og_path);
		}
		return ;
	}
	if (chdir(path) == -1) //this is probably fuckin unnecessary at this point
		printf("fucking chdir\n");
	return ;
} */


/////

void    home_dir(t_bigshell *data)
{
    char    *home;

    home = getenv("HOME");
    if (!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        return ;
    }
    overwrite_pwd(data, home);
}

char    *free_NULL(char *str)
{
    if (str)
        free(str);
    return (NULL);
}

char    *get_cwd(t_bigshell *data)
{
    data->buffer_size = BUFFER;
    while (1)
    {
        if (data->cwd)
            break ;
        data->cwd = malloc(sizeof(char) * data->buffer_size);
        if (!data->cwd)
        {
            free(data->cwd);
            CRITICAL_FAILURE(data, "cd: malloc failed in cd.c:go_back");
        }
        getcwd(data->cwd, data->buffer_size);
        if (!data->cwd && errno == ERANGE)
        {
            data->cwd = free_NULL(data->cwd);
            data->buffer_size += BUFFER_INCREMENT;
        }
        if (!data->cwd && errno != ERANGE)
        {
            data->cwd = free_NULL(data->cwd);
            simple_error_message(data, "minishell: cd: unable to get current directory\n", 1);
            break ;
        }
    }
    return (data->cwd);
}

void    ft_cd(t_bigshell *data)
{
    t_token *arg;
    char    *cwd;

    cwd = NULL;
    arg = data->commands->args;
    if (data->commands->arg_num > 1)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        update_exit_stat(data, 1);
        return ;
    }
    if (!arg || ft_strncmp(arg->str, "~", ft_strlen(arg->str)) == 0)
	{
       home_dir(data);
	   return ;
	}
    if (arg->str[0] == '/')
    {
        printf("minishell: cd: %s: No such file or directory\n", arg->str);
        update_exit_stat(data, 1);
        return ;
    }
    else
    {
        //change_dir(data, arg->str);
        if (chdir(arg->str) == -1)
        {
            printf("minishell: cd: %s: No such file or directory\n", arg->str);
            update_exit_stat(data, 1);
            return ;
        }
        cwd = get_cwd(data);
        if (!cwd)
        {
            simple_error_message(data, "minishell: cd.c: cwd failed\n", 1);
            return ;
        }
        overwrite_pwd(data, cwd);
    }
}
