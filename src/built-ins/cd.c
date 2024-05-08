/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/08 12:36:53 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


//This function takes a full path as input and removes the last directory from it.
/* char	*delete_tail(char *full_path)
{
	char	*end; 
	
	if (!full_path)
		return (NULL);
	end = ft_strrchr(full_path, '/');
	if (!end)
		return (NULL);
	*end = 0;
	return (full_path);
} */

void	overwrite_s_env(t_bigshell *data, char *env_var, char *str)
{
	t_env	*tmp;

	tmp = data->s_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, env_var, ft_strlen(tmp->var)) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(str);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "minishell: cd: strdup failed in overwrite_s_env");
			break ;
		}
		tmp = tmp->next;
	}
}

void	overwrite_oldpwd(t_bigshell *data, char *oldpwd)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "OLDPWD", ft_strlen(tmp->var)) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
			tmp->value = ft_strdup(oldpwd);
			if (!tmp->value)
				CRITICAL_FAILURE(data, "minishell: cd: strdup failed in overwrite_oldpwd");
			break ;
		}
		tmp = tmp->next;
	}
	overwrite_s_env(data, "OLDPWD", oldpwd);
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
	overwrite_s_env(data, "PWD", new_path);
}

void    home_dir(t_bigshell *data, char *oldpwd)
{
    char    *home;

    home = getenv("HOME");
    if (!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        return ;
    }
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		//printf("minishell: cd: %s: No such file or directory\n", home);
        update_exit_stat(data, 1);
        return ;
	}
	overwrite_oldpwd(data, oldpwd);
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
	data->cwd = NULL;
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
        if (errno == ENOENT)
			return(free_NULL(data->cwd), NULL);
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
	char	*path;
	char	*oldpwd;

    cwd = NULL;
    arg = data->commands->args;
	oldpwd = get_cwd(data);
    if (data->commands->arg_num > 1)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        update_exit_stat(data, 1);
        return ;
    }
    if (!arg)
	{
       home_dir(data, oldpwd);
	   free(oldpwd);
	   update_exit_stat(data, 0);
	   return ;
	}
    else
    {
		path = arg->str;
        if (chdir(path) != 0)
        {
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
            //printf("minishell: cd: %s: No such file or directory\n", arg->str);
            update_exit_stat(data, 1);
			free(oldpwd);
            return ;
        }
		//data->cwd = NULL;
        cwd = get_cwd(data);
		//printf("cwd = %s\n", cwd);
        if (!cwd)
        {
            simple_error_message(data, "minishell: cd.c: cwd failed", 1);
            return ;
        }
		overwrite_oldpwd(data, oldpwd);
        overwrite_pwd(data, cwd);
		free(cwd);
		free(oldpwd);
		update_exit_stat(data, 0);
    }
}
