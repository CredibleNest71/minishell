/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:10:32 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/07 18:34:32 by ischmutz         ###   ########.fr       */
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
		return ("echo -n");
	else if (index == 1)
		return ("cd");
	else if (index == 2)
		return ("pwd");
	else if (index == 3)
		return ("export");
	else if (index == 4)
		return ("unset");
	else if (index == 5)
		return ("env");
	else if (index == 6)
		return ("exit");
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

void	builtin_exec(t_bigshell *data, int builtin_index, int cmd_index)
{
	if (builtin_index == 0)
	{
		if (ft_strncmp(data->commands[cmd_index]->args[0]->str, "-n", 2) == 0)
			ft_echo(data->commands[cmd_index]->args, 1);
		ft_echo(data->commands[cmd_index]->args, 0);
	}
	/* else if (builtin_index == 1)
		ft_cd();
	else if (builtin_index == 2)
		ft_pwd();
	else if (builtin_index == 3)
		ft_export();
	else if (builtin_index == 4)
		ft_unset();
	else if (builtin_index == 5)
		ft_env();
	else if (builtin_index == 6)
		ft_exit(); */
}

void	builtin_check_exec(t_bigshell *main, char *cmd, int cmd_index)
{
	int		len;
	int		i;
	
	i = 0;
	len = ft_strlen(cmd);
	while (main->built_ins[i] != NULL)
	{
		printf("%s\n", main->built_ins[i]);
		printf("hola\n");
		if (ft_strncmp(cmd, main->built_ins[i], len) == 0)
		{
			printf("hola\n");
			builtin_exec(main, i, cmd_index);
			//printf("built in found"); //exec built-in
			printf("hola\n");
		}
		i++;
	}
	printf("hej\n");
	return ;
}

/* while (list[i])
{
	i++;
} */
