/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:34:54 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/09 10:55:09 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

enum type
{
	CMD = 0,
	ARG,
	PATH,
	NEX,
	DIR,
}	typedef e_type;

struct	s_token
{
	char 	*str;
	int		type;
	char	*dir;
}	typedef t_token;

struct	s_command
{
	t_token				*input;		//<
	t_token				*output;	//>
	t_token				*cmd;		//command
	t_token				**args;		//arguments
	int					arg_num;
	t_token				*nexus;		//PIPE?
}	typedef t_command;

struct	s_bigshell
{
	t_command	**commands;
	int			num_cmd;
	int			exit_stat;
	int			pipe_fd[2];
	int			id;
	char		**env;
	char		**variables;
	char		**built_ins;
}	typedef t_bigshell;


void	store_restore_fds(int mode);
void	check_file(const char *file, int mode);
void	redir(t_command *cmd_struct, t_bigshell *main_struct);

char	**find_and_split_path(char **env);
char	*check_if_correct_path(char **paths, t_bigshell *main, char *str);

char	*put_str(char *s);
void	put_built_in(int index, t_bigshell *data);
void	built_in_list(t_bigshell *data);
void	builtin_exec(t_bigshell *data, int builtin_index, int cmd_index);
void	builtin_check_exec(t_bigshell *main, char *cmd, int cmd_exec);

void	simple_error(t_bigshell *data, int exit_code);
void	fatal_error(t_bigshell *data, int exit_code);

void	simple_exec(t_bigshell *data);

void	ft_echo(t_token **args, int option);
void	ft_cd(t_bigshell *data, int index);
void	ft_pwd(t_bigshell *data);

#endif
