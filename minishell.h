/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:34:54 by ischmutz          #+#    #+#             */
/*   Updated: 2024/02/29 11:30:56 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
//# include <readline/readline.h>
//# include <readline/history.h>
# include "libft/libft.h"

typedef enum type
{
	CMD = 0,
	ARG,
	PATH,
	NEX,
	DIR,
}	e_type;

typedef struct	s_token
{
	char 			*str;
	int				type;
	char			*dir;
	struct s_token	*next;
}	t_token;

typedef struct	s_command //linked list now (have to iterate through nodes)
{
	t_token				*input;		//<
	t_token				*output;	//>
	t_token				*cmd;		//command
	t_token				*args;		//arguments
	int					arg_num;
	t_token				*nexus;		//PIPE?
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;


typedef struct	s_bigshell
{
	t_command	*commands;
	int			num_cmd;
	int			exit_stat;
	int			pipe_fd[2];
	int			id;
	int			var_i;	//counts how many variables exist in the environment
	int			reference_i; //keeps count of data->env 
	char		*export_var; //tf is this
	char		**og_env; //do I use u?
	char		**mod_env; //do I use u?
	t_env		*env;
	t_env		*s_env;
	char		**built_ins;
}	t_bigshell;


void	store_restore_fds(int mode);
void	check_file(const char *file, int mode);
void	redir(t_command *command, t_bigshell *data);

char	**find_and_split_path(char **env);
char	*check_if_correct_path(char **paths, t_bigshell *data, char *str);

char	*put_str(char *s);
void	put_built_in(int index, t_bigshell *data);
void	built_in_list(t_bigshell *data);
void	builtin_exec(t_bigshell *data, int builtin_index);
void	builtin_check_exec(t_bigshell *data, char *cmd);

void	simple_error(t_bigshell *data, int exit_code);
void	fatal_error(t_bigshell *data, int exit_code);

void	simple_exec(t_bigshell *data);

void	ft_echo(t_token *args, int option);
void	ft_cd(t_bigshell *data);
void	ft_pwd(t_bigshell *data);

void	ft_export(t_bigshell *data);
int		check_if_sorted(t_env *current);
void	switch_values(t_env *current);
void	sort_env(t_bigshell *data);
void	print_env(t_env *head);
void	make_copy(t_bigshell *data);

void	ft_unset(t_bigshell *data);
void	unset_var(t_bigshell *data, t_env **current, t_env **prev);
void	find_node_to_delete(t_bigshell *data, t_env **current, t_env **prev, t_token *arg);

void	ft_env(t_bigshell *data, int option);
void	add_env_variable(t_bigshell *data);

void	ft_exit(t_bigshell *data);

t_env   *create_node(t_bigshell *data, char *str);
void    store_env(t_bigshell *data, char **env);
void    convert_env(t_bigshell *data);

void	free_single_node(t_bigshell *data, t_env **node);
void	free_env(t_bigshell *data);
void	free_builtin_list(t_bigshell *data);
void	free_tokens(t_token *data);
void	free_commands(t_bigshell *data);
void	free_struct(t_bigshell *data);

#endif
