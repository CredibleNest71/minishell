/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:27 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/11 19:52:52 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h" 
#include "../../parser/parse.h"
#include "../../main/sig.h"
//#include <iterator>
#include <stdio.h>
#include <unistd.h>

//checks for expansion suppression
//hex code of ' == 27
char	*check_for_quotes(t_bigshell *data, char *eof)
{
	int		i;
	size_t	j;
	char	*delimiter;

	i = 0;
	j = -1;
	if (!ft_strlen(eof))
		return (ft_strdup(""));
	delimiter = malloc(sizeof(char) * (ft_strlen(eof) - 1));
	if (!delimiter)
		critical_failure(data, "heredoc.c:97 malloc failed");
	if (eof[i] == '"' || eof[i] == '\'')
	{
		while (++i < (int)ft_strlen(eof))
		{
			delimiter[++j] = eof[i];
		}
		delimiter[j] = '\0';
		return (delimiter);
	}
	free(delimiter);
	delimiter = ft_strdup(eof);
	if (!delimiter)
		return (free(delimiter), NULL);
	return (delimiter);
}

static void	write_to_fd(int heredoc_fd, char *lineread)
{
	write(heredoc_fd, lineread, ft_strlen(lineread));
	write(heredoc_fd, "\n", 1);
}

static void	ft_heredoc2(t_bigshell *data, t_command *cmd, t_token *input)
{
	char	*mod_eof;
	char	*lineread;
	int		heredoc_fd;

	lineread = NULL;
	mod_eof = check_for_quotes(data, input->str);
	cmd->tmpfile = create_unique_name(data, cmd, mod_eof);
	heredoc_fd = open_heredoc_fd(data, cmd);
	while (1)
	{
		if (g_sig == SIGINT)
			return (close_heredoc_fd(heredoc_fd), free(mod_eof));
		lineread = readline("> ");
		if (!lineread || !(ft_strncmp(mod_eof, lineread,
					ft_strlen(mod_eof) + 1)))
			break ;
		if (!input->quoted)
			lineread = expand(lineread, data);
		write_to_fd(heredoc_fd, lineread);
		free(lineread);
	}
	if (!lineread)
		ft_putstr_fd("minishell: warning: heredoc wanted delimiter\n", 2);
	mod_eof = free_set_null(mod_eof);
	close_heredoc_fd(heredoc_fd);
}

void	ft_heredoc(t_bigshell *data)
{
	t_command	*cmd;
	t_token		*input;

	if (!data->heredoc)
		return ;
	cmd = data->commands;
	set_signals(2);
	while (cmd)
	{
		input = cmd->input;
		while (input)
		{
			if (input->type == (enum type)HEREDOC)
			{
				ft_heredoc2(data, cmd, input);
				if (g_sig == SIGINT)
					return (update_exit_stat(data, 130));
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
}
