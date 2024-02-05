/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:10:32 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/05 18:09:23 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*put_str(char *s)
{
	int		len;
	int		i;
	char	*str;

	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	i = -1;
	while (str[++i])
		str[i] = s[i];
	return (str);
}

char	*put_built_in(int index)
{
	if (index == 0)
		return (put_str("echo -n"));
	else if (index == 1)
		return (put_str("cd"));
	else if (index == 2)
		return (put_str("pwd"));
	else if (index == 3)
		return (put_str("export"));
	else if (index == 4)
		return (put_str("unset"));
	else if (index == 5)
		return (put_str("env"));
	else if (index == 6)
		return (put_str("exit"));
	return (NULL);
}

char	**built_in_list(t_bigshell *data)
{
	char	**list;
	int		i;

	i = 0;
	list = malloc(7 * sizeof(char *));
	while (i < 7)
	{
		list[i] = put_built_in(i);
		if (!list[i])
			data->exit_stat = 1;
			//protecc
		i++;
	}
	list[i] = NULL;
	return (list);
}

void	builtin_exec(t_bigshell *main, int index) //index = command index
{
	int		len;
	int		i;
	char	**path;
	char	*correct_path;
	
	i = 0;
	len = ft_strlen((const char *)main->commands[index]->cmd);
	while (main->built_ins[i] != NULL)
	{
		if (ft_strncmp((const char *)main->commands[index]->cmd, main->built_ins[i], len) == 0)
			printf("built in found"); //exec built-in
		i++;
	}
	path = find_and_split_path(main->env);
	if (!path)
		printf("find&split failed"); //shit has been allocated
	correct_path = check_if_correct_path(path, main, main->commands[index]->cmd->str, i);
	if (!correct_path)
		printf("correct path not found"); //do smt
	execve(correct_path, (char *const *)main->commands[index]->cmd, main->env);
	//protect execve
	
}

/* while (list[i])
{
	i++;
} */