/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:19 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/08 16:56:24 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <unistd.h>

char	**find_and_split_path(char **env)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	while (env[++i] != 0)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(env[i] + 5);
			if (!path)
				return (s_array_free(env), NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (s_array_free(env), NULL);
			return (paths);
		}
	}
	return (NULL);
}

char	*check_path(t_bigshell *data, char *str)
{
	if (!str[0])
		return (NULL);
	if (access(str, X_OK) == -1)
	{
		perror("minishell");
		if (errno == EACCES)
			return (exit_child(data, 126), NULL);
		if (errno == ENOENT)
			return (exit_child(data, 127), NULL);
	}
	return (ft_strdup(str));
}

char	*check_unset_path(t_bigshell *data, char *str)
{
	char	*tmp;
	char	*to_check;
	
	tmp = NULL;
	if (access(str, F_OK) == 0)
	{
		tmp = ft_strjoin(get_cwd(data), "/");
		if (!tmp)
			return (CRITICAL_FAILURE(data, "pathfinder.c: tmp: strjoin failed"), NULL);
		to_check = ft_strjoin(tmp, str);
		if (!to_check)
			return (free(tmp), CRITICAL_FAILURE(data, "pathfinder.c: to_check: strjoin failed"), NULL);
		if (access(to_check, X_OK) == 0)
			return (free(tmp), to_check);
		free(tmp);
		free(to_check);
	}
	return (tmp);
}

// what if cmd path is sth like foo/bar/executable
char	*check_if_correct_path(char **paths, t_bigshell *data, char *str)
{
	int		i;
	char	*tmp;
	char	*to_check;

	i = 0;
	// if (!str[0] || str[0] == '/' || str[0] == '.')
	// 	return (check_path(data, str));
	if (!str[0])
		return (NULL);
	if (str[0] == '/' || str[0] == '.')
		return (ft_strdup((char *)str));
	while (paths && paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return(double_free_array(paths, data->mod_env), CRITICAL_FAILURE(data, "pathfinder.c: tmp: strjoin failed"), NULL);
		to_check = ft_strjoin(tmp, str);
		if (!to_check)
			return(double_free_array(paths, data->mod_env), free(tmp), CRITICAL_FAILURE(data, "pathfinder.c: to_check: strjoin failed"), NULL);
		if (access(to_check, X_OK) == 0)
			return (free(tmp), to_check);
		free(tmp);
		free(to_check);
		i++;
	}
	return (check_unset_path(data, str));
}


