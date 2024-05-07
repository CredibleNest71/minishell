/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:55:27 by ischmutz          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:04 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h" 
#include "../parser/parse.h"
#include "../main/sig.h"
//#include <iterator>
#include <stdio.h>
#include <unistd.h>

int	tmpfile_cleanup(t_bigshell *data)
{
	t_command	*cmd;
	
	cmd = data->commands;
	while (cmd)
	{
		if (cmd->tmpfile)
		{
			//close(cmd->heredoc_fd);
			if (unlink(cmd->tmpfile) == -1)
				simple_error(data, 1);
		}
		cmd = cmd->next;
	}
	free_tmpfile(data);
	return (0);
}

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
	size_t	j;
	char	*delimiter;
	
	i = 0;
	j = -1;
	delimiter = malloc(sizeof(char) * (ft_strlen(eof) - 1));
	if (!delimiter)
		CRITICAL_FAILURE(data, "heredoc.c:97 malloc failed");
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
	int			heredoc_fd;
	int			i;
	t_command	*cmd;
	t_token		*input;
	
	i = 0;
	cmd = data->commands;
	set_signals(2);
	while (cmd)
	{
		input = cmd->input;
		while (input)
		{
			if (input->type == (enum type)HEREDOC)
			{
				lineread = NULL;
				eof = input->str;
				mod_eof = check_for_quotes(data, eof);
				cmd->tmpfile = ft_strjoin("tmpfile", input->str);
				if (!cmd->tmpfile)
					simple_error(data, 1); //check if correct error handling
				heredoc_fd = open(cmd->tmpfile, O_CREAT | O_TRUNC | O_RDWR, 00644);
				if (heredoc_fd == -1)
					simple_error(data, 1);
				while (1)
				{
					if (g_sig == SIGINT)
						break ;
					lineread = readline("> ");
					if (!lineread || !(ft_strncmp(mod_eof, lineread, ft_strlen(mod_eof) + 1)))
						break ;
					if (!input->quoted)
						lineread = expand(lineread, data);
					write(heredoc_fd, lineread, ft_strlen(lineread));
					write(heredoc_fd, "\n", 1);
					free(lineread);
				}
				if (!lineread)
					printf("minishell: warning: heredoc (wanted '%s')\n", eof);
				// if (!cmd->cmd)
				// {
				// 	if(close(heredoc_fd) == -1)
				// 		simple_error(data, 1);
				// 	unlink(cmd->tmpfile);
				// }
				free(mod_eof);
				mod_eof = NULL;
				if (heredoc_fd)
				{
					if (close(heredoc_fd) == -1)
						perror("close heredoc:");
					heredoc_fd = -1;
				}
				eof = NULL;
			}
			input = input->next;
		}
		cmd = cmd->next;
	}
}

//heredoc going through heredoc linked list
// void	ft_heredoc(t_bigshell *data)
// {
// 	char		*lineread;
// 	char		*eof;
// 	char		*mod_eof;
// 	char		*tmpfile;
// 	//char		*eof_mod;
// 	int			heredoc_fd;
// 	int			i;
// 	t_token		*input;

// 	i = 0;
// 	input = data->heredoc;
// 	set_signals(2);
// 	//eof = delimiter_finder(data);
// 	//if (!eof)
// 	//	simple_error(data, 1);
// 	//eof_mod = check_for_quotes(data, eof);
// 	while (input)
// 	{
// 		lineread = NULL;
// 		eof = input->str;
// 		mod_eof = check_for_quotes(data, eof);
// 		printf("%s\n", mod_eof); //debugging
// 		tmpfile = ft_strjoin("tmpfile", input->str);
// 		heredoc_fd = open(tmpfile, O_CREAT | O_TRUNC | O_RDWR, 00644);
// 		free(tmpfile);
// 		if (heredoc_fd == -1)
// 			simple_error(data, 1);
// 		while (1)
// 		{
// 			if (g_sig == SIGINT)
// 				break ;
// 			lineread = readline("> ");
// 			//printf("%s\n", eof_mod);
// 			if (!lineread || !(ft_strncmp(mod_eof, lineread, ft_strlen(mod_eof) + 1)))
// 				break ;
// 			if (eof[i] != '"' || eof[i] == 27) //ask willem about heredoc expansion
// 				lineread = expand(lineread, data);
// 			write(heredoc_fd, lineread, ft_strlen(lineread));
// 			write(heredoc_fd, "\n", 1); //possibly problematic
// 			//printf("%s\n", lineread);
// 			//free(lineread);
// 		}
// 		if (!lineread)
// 		{
// 			printf("minishell: warning: heredoc (wanted '%s')\n", eof);
// 			close(heredoc_fd);
// 			unlink("tmpfile.txt");
// 		}
// 		input = input->next;
// 	}
// 	//pass tmpfile.txt to execution
// 	//after execution check for tmpfile and delete it
// 	if (!data->commands->cmd)
// 	{
// 		close(heredoc_fd);
// 		unlink("tmpfile.txt");
// 		return ;
// 	}
// 	/* if (!data->commands) //struct is always present so this is never true
// 		return ; */ //heredoc no hace nada sin un cmd pero el tmpfile tiene que ser deleted
// 	else
// 		data->heredoc_fd = heredoc_fd;
// }
