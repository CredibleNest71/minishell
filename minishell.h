/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:34:54 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/14 14:45:54 by ischmutz         ###   ########.fr       */
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
# include <errno.h>
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

//# include "src/parser/parse.h"

# ifndef BUFFER
# define BUFFER 50
# endif

# ifndef BUFFER_INCREMENT
# define BUFFER_INCREMENT 50
# endif

typedef enum type {
	CMD = 0,
	ARG,
	IN,
	OUT,
	HEREDOC,
	APP,
	PIPE,
}	 e_type;

typedef struct	s_token
{
	char 			*str;
	char			*delimiter;
	int				type;
	char			*dir;
	int				connected;
	int				distanced;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_command
{
	t_token				*cmd;		//command
	t_token				*args;		//arguments
	char				**args_exec;
	t_token				*input;		//< / heredoc
	t_token				*output;	//> / append
	int					arg_num;
	struct s_command	*next;
}	 t_command;

typedef struct s_env
{
	char			*var; //previously str
	char			*value;
	struct s_env	*next;
}	t_env;


typedef struct	s_bigshell
{
	int			num_cmd;
	//int			exit_stat; storing exit stat in env
	int			simple_error; //this will be set with stdlib macros to define whether I need to exit the minishell
	int			pipe_fd[2];
	int			id;
	int			var_i;	//counts how many variables exist in the environment
	int			reference_i; //keeps count of data->env
	int			std_in; //stored std_in
	int			std_out; //stored std_out
	int			fd_in; //redirected in
	int			fd_out; //redirected out
	char		*export_var; //tf is this
	char		**og_env; //do I use u?
	char		**mod_env;
	char		**built_ins;
	t_token		*heredoc;	//token with delimiter and str; 
	t_command	*commands;
	char		*prompt;
	char		*terminal_prompt;
	t_env		*env;
	t_env		*s_env;
}	t_bigshell;


typedef struct s_signal
{
	int			sigint;
	int			sigquit;
	int			pid;
	t_bigshell *data;
}	t_sig;

void	store_restore_fds(t_bigshell *data, int mode);
int		check_file(t_bigshell *data, const char *file, int mode);
int		redir(t_command *command, t_bigshell *data);

char	**find_and_split_path(char **env);
char	*check_if_correct_path(char **paths, t_bigshell *data, char *str);

char	*put_str(char *s);
void	put_built_in(int index, t_bigshell *data);
void	built_in_list(t_bigshell *data);
void	builtin_exec(t_bigshell *data, int builtin_index);
int		builtin_check_exec(t_bigshell *data, char *cmd);

int		builtin_allrounder(t_bigshell *data);

void	update_exit_stat(t_bigshell *data, int exit_code);
void	redir_error(t_bigshell *data, int exit_code, char *str);
void	simple_error(t_bigshell *data, int exit_code);
void	CRITICAL_FAILURE(t_bigshell *data, char *str);

void	simple_exec(t_bigshell *data);

void	pipe_fork(t_bigshell *data);
void	complex_exec(t_bigshell *data, t_token *cmd);

void	ft_echo(t_token *args);
void	ft_cd(t_bigshell *data);
void	ft_pwd(t_bigshell *data);

void	ft_export(t_bigshell *data);
int		check_if_sorted(t_env *current);
void	switch_nodes(t_env *current);
void	sort_env(t_bigshell *data);
void	print_env(t_env *head);
void	make_copy(t_bigshell *data);
int		check_var(t_bigshell *data, char *key);
void	switch_values(t_bigshell *data, t_env *node, char	*new_value, int len);
int		var_exists(t_bigshell *data, char *str);

void	ft_unset(t_bigshell *data);
void	unset_var(t_bigshell *data, t_env **current, t_env **prev);
void	find_node_to_delete(t_bigshell *data, t_env **current, t_env **prev, t_token *arg);

void	ft_env(t_bigshell *data);
//void	add_env_variable(t_bigshell *data);

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

void	ft_heredoc(t_bigshell *data);
char	*delimiter_finder(t_bigshell *data);
char	*check_for_quotes(t_bigshell *data, char *eof);
int		heredoc_finder(t_bigshell *data);

#endif
