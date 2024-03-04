/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:27 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/04 12:46:39 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


//${SRC_DIR}${EXEC_DIR}heredoc.c\
//00644 = S_IRUSR | S_IWUSR
//ft_heredoc creates a tmp file that will be deleted the moment heredoc_fd is closed
//heredoc_fd = open(".", O_TMPFILE | O_RDWR | S_IRUSR | S_IWUSR);
/* if (lineread == EOF || lineread == NULL) //if delimiter is found then exit loop
	break ; */
//if heredoc fails nothing gets executed
void	ft_heredoc(t_bigshell *data)
{
	char		*lineread;
	int			heredoc_fd;

	lineread = NULL;
	heredoc_fd = open("tmpfile.txt", O_CREAT | O_TRUNC | O_RDWR, 00644);
	if (heredoc_fd == -1)
		simple_error(data, 1);
	while (1)
	{
		lineread = readline("> ");
		if (lineread == data->commands->heredoc->str || lineread == NULL)
			break ;
		//have to check for expansions and access that
		//ex. cat << heredoc EOF
		//> print the path: $path
		//EOF
		write(heredoc_fd, lineread, ft_strlen(lineread));
	}
	//pass tmpfile.txt to execution
	//after execution check for tmpfile and delete it
}


/* int	main()
{
	t_bigshell data;
	char *lineread;
	lineread = readline("tinyshell: ");
	data.commands = parse(lineread);
	ft_heredoc(&data);
} */