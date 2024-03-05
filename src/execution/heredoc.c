/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:27 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/05 14:20:47 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../parser/parse.h"
#include <unistd.h>


//checks for delimiter
char	*delimiter_finder(t_bigshell *data)
{
	t_token *tmp_input;
	char	*delimiter;
	
	delimiter = NULL;
	tmp_input = data->commands->input;
	while (tmp_input)
	{
		if (tmp_input->type == (enum type) HEREDOC)
			delimiter = tmp_input->str;
		tmp_input = tmp_input->next;
	}
	return (delimiter);
}

//${SRC_DIR}${EXEC_DIR}heredoc.c
//00644 = S_IRUSR | S_IWUSR
//ft_heredoc creates a tmp file that will be deleted the moment heredoc_fd is closed
//heredoc_fd = open(".", O_TMPFILE | O_RDWR | S_IRUSR | S_IWUSR);
/* if (lineread == EOF || lineread == NULL) //if delimiter is found then exit loop
	break ; */
//if heredoc fails nothing gets executed
void	ft_heredoc(t_bigshell *data)
{
	char		*lineread;
	char		*eof;
	int			heredoc_fd;

	lineread = NULL;
	eof = delimiter_finder(data);
	/* if (!eof)
		simple_error(data, 1); */
	heredoc_fd = open("tmpfile.txt", O_CREAT | O_TRUNC | O_RDWR, 00644);
	if (heredoc_fd == -1)
		simple_error(data, 1);
	while (1)
	{
		lineread = readline("> ");
		if (lineread == eof || lineread == NULL)
		 	break ;
		lineread = expand(lineread);
		write(heredoc_fd, lineread, ft_strlen(lineread));
		write(heredoc_fd, "\n", 1);
		//printf("%s\n", lineread);
	}
	//pass tmpfile.txt to execution
	//after execution check for tmpfile and delete it
}
