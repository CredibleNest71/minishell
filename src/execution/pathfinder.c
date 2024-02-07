/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:33:19 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:49 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

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
			path = ft_strdup(env[i]);
			if (!path)
				return (NULL);
			paths = ft_split(path, ':');
			free(path);
			if (!paths)
				return (NULL);
			return (paths);
		}
	}
	return (0);
}

char	*check_if_correct_path(char **paths, t_bigshell *main, char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	*to_check;

	i = 0;
	j = 0;
	//check if paths &cmd exist?
	//do I have to take care of absolute n relative paths 4 commands?
	if (str[0] == '/' || str[0] == '.')
		return ((char *)str);
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			fatal_error(main, 1);
		to_check = ft_strjoin(tmp, str);
		if (!to_check)
			fatal_error(main, 1);
		if (access(to_check, X_OK) == 0)
			return (to_check);
		free(to_check);
		i++;
	}
	return (NULL);
}
