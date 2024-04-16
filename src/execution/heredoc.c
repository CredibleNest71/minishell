/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:27 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/16 15:46:03 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" 
#include "../parser/parse.h"
#include "../main/sig.h"
//#include <iterator>
#include <stdio.h>
#include <unistd.h>

//heredoc_finder is in minishell.c (here 4 testing purposes)
int	heredoc_finder(t_bigshell *data)
{
	t_token	*tmp;

	if (!data->commands->cmd)
	{
		if (data->heredoc)
			return(0);
	}
	else
	{
		tmp = data->commands->input;
		while (tmp)
		{
			if (tmp->type == (enum type) HEREDOC)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

//checks for delimiter
/* char	*delimiter_finder(t_bigshell *data)
{
	t_token *tmp_input;
	char	*delimiter;
	
	delimiter = NULL;
	if (!data->commands)
	{
		if (!data->heredoc)
			return (NULL);
		delimiter = data->heredoc->str; //->delimiter changed to str
		return (delimiter);
	}
	tmp_input = data->commands->input;
	while (tmp_input)
	{
		if (tmp_input->type == (enum type) HEREDOC)
			delimiter = tmp_input->str; //->delimiter changed to str
		tmp_input = tmp_input->next;
	}
	return (delimiter);
} */

//checks for expansion suppression
//hex code of ' == 27
char	*check_for_quotes(t_bigshell *data, char *eof)
{
	int		i;
	size_t		j;
	char	*delimiter;
	
	i = 0;
	j = -1;
	delimiter = malloc(sizeof(char) * (ft_strlen(eof) - 1));
	if (!delimiter)
		CRITICAL_FAILURE(data, "heredoc: malloc failed");
	if (eof[i] == '"' || eof[i] == '\'')
	{
		while (++i < (int)ft_strlen(eof))
		{
			delimiter[++j] = eof[i];
		//	printf("%zu\n %zu\n", j, i);
		}
		delimiter[j] = '\0'; //am I overwriting shit?
		//printf("%zu\n", j); //what do u do
		//printf("%s\n", delimiter); //what do u do
		return (delimiter);
	}
	delimiter = eof;
	return (delimiter);
}

//${SRC_DIR}${EXEC_DIR}heredoc.c
//00644 = S_IRUSR | S_IWUSR
//ft_heredoc creates a tmp file that will be deleted the moment heredoc_fd is closed
//heredoc_fd = open(".", O_TMPFILE | O_RDWR | S_IRUSR | S_IWUSR);
/* if (lineread == EOF || lineread == NULL) //if delimiter is found then exit loop
	break ; */
//if heredoc fails nothing gets executed

char	*find_eof(t_token *input)
{
	t_token	*tmp;

	tmp = input;
	while (tmp)
	{
		if (tmp->type == (enum type)HEREDOC)
			return(tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_heredoc(t_bigshell *data)
{
	char		*lineread;
	char		*eof;
	char		*mod_eof;
	//char		*eof_mod;
	int			heredoc_fd;
	int			i;
	t_token		*input;

	i = 0;
	input = data->heredoc;
	set_signals(2);
	//eof = delimiter_finder(data);
	//if (!eof)
	//	simple_error(data, 1);
	//eof_mod = check_for_quotes(data, eof);
	while (input)
	{
		lineread = NULL;
		eof = input->str;
		mod_eof = check_for_quotes(data, eof);
		printf("%s\n", mod_eof);
		heredoc_fd = open("tmpfile.txt", O_CREAT | O_TRUNC | O_RDWR, 00644);
		if (heredoc_fd == -1)
			simple_error(data, 1);
		while (1)
		{
			if (g_sig = SIGINT)
				break ;
			lineread = readline("> ");
			//printf("%s\n", eof_mod);
			if (!lineread || !(ft_strncmp(mod_eof, lineread, ft_strlen(mod_eof) + 1)))
				break ;
			if (eof[i] != '"' || eof[i] == 27) //ask willem about heredoc expansion
				lineread = expand(lineread, data);
			write(heredoc_fd, lineread, ft_strlen(lineread));
			write(heredoc_fd, "\n", 1); //possibly problematic
			//printf("%s\n", lineread);
		}
		if (!lineread)
		{
			printf("minishell: warning: heredoc (wanted '%s')\n", eof);
			close(heredoc_fd);
			unlink("tmpfile.txt");
		}
		input = input->next;
	}
	//pass tmpfile.txt to execution
	//after execution check for tmpfile and delete it
	if (!data->commands->cmd)
	{
		close(heredoc_fd);
		unlink("tmpfile.txt");
		return ;
	}
	/* if (!data->commands) //struct is always present so this is never true
		return ; */ //heredoc no hace nada sin un cmd pero el tmpfile tiene que ser deleted
	else
		data->heredoc_fd = heredoc_fd;
}
