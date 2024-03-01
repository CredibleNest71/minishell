/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:27 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/01 17:39:33 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


//${SRC_DIR}${EXEC_DIR}heredoc.c\
//00644 = S_IRUSR | S_IWUSR
//ft_heredoc creates a tmp file that will be deleted the moment heredoc_fd is closed
void	ft_heredoc(t_bigshell *data)
{
	char		*lineread;
	int			heredoc_fd;

	lineread = NULL;
	heredoc_fd = open(".", O_TMPFILE | O_RDWR | S_IRUSR | S_IWUSR);
	
	while (1)
	{
		lineread = readline("> ");
		/* if (lineread == EOF || lineread == NULL) //if delimiter is found then exit loop
			break ; */
		
	}
}
