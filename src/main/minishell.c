/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:33:48 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/05 12:15:03 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parser/parse.h"
#include <stdio.h>
#include <unistd.h>


//checks if there's a heredoc present in the cmd line
int	heredoc_finder(t_bigshell *data)
{
	t_token	*tmp;

	tmp = data->commands->input;
	while (tmp)
	{
		if (tmp->type == (enum type) HEREDOC)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_bigshell	data;
	char		*lineread;
	int			i;

	lineread = NULL;
	ft_bzero(&data, sizeof(data));
	data.og_env = env;
	data.built_ins = (char **)malloc(sizeof(char *) * 8);
	built_in_list(&data);
	i = 0;
	while (1)
	{
	    lineread = readline("shitshell: ");
		data.commands = parse(lineread);
		//print_cmds(data.commands);
		store_restore_fds(1); //will store stdin & stdout
		if (data.num_cmd == 1)
		{
			if (heredoc_finder(&data) == 0)
				ft_heredoc(&data);
			if ((data.id = fork()) == -1)
				fatal_error(&data, 1);
			if (data.id == 0)
				simple_exec(&data);
		}
		else
		{
			while (i < data.num_cmd)
			{
				if (heredoc_finder(&data) == 0)
					ft_heredoc(&data);
				if ((data.id = fork()) == -1)
					fatal_error(&data, 1);
				if (data.id == 0)
					complex_exec(data, i);
				i++;
			}
		}
	}
	return (0);
}
