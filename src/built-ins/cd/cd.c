/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:36 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/09 19:25:49 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	home_dir(t_bigshell *data, char *oldpwd)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return ;
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		update_exit_stat(data, 1);
		return ;
	}
	overwrite_oldpwd(data, oldpwd);
	overwrite_pwd(data, home);
}

char	*free_null_cd(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*get_cwd(t_bigshell *data)
{
	data->cwd = NULL;
	data->buffer_size = BUFFER;
	while (1)
	{
		if (data->cwd)
			break ;
		data->cwd = malloc(sizeof(char) * data->buffer_size);
		if (!data->cwd)
			critical_failure(data, "cd: malloc failed in cd.c:go_back");
		getcwd(data->cwd, data->buffer_size);
		if (errno == ENOENT)
			return (free_null_cd(data->cwd), NULL);
		if (!data->cwd && errno == ERANGE)
		{
			data->cwd = free_null_cd(data->cwd);
			data->buffer_size += BUFFER_INCREMENT;
		}
		if (!data->cwd && errno != ERANGE)
		{
			data->cwd = free_null_cd(data->cwd);
			error1(data, "minishell: cd: unable to get current directory", 1);
			break ;
		}
	}
	return (data->cwd);
}

void	ft_cd2(t_bigshell *data, t_token *arg, char *cwd, char *oldpwd)
{
	char	*path;

	path = arg->str;
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		update_exit_stat(data, 1);
		free(oldpwd);
		return ;
	}
	cwd = get_cwd(data);
	if (!cwd)
	{
		error1(data, "minishell: cd.c: cwd failed", 1);
		return ;
	}
	overwrite_oldpwd(data, oldpwd);
	overwrite_pwd(data, cwd);
	free(cwd);
	free(oldpwd);
	update_exit_stat(data, 0);
}

void	ft_cd(t_bigshell *data)
{
	t_token	*arg;
	char	*cwd;
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
		ft_cd2(data, arg, cwd, oldpwd);
}
