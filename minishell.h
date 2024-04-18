/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:34:54 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/16 14:10:04 by mresch           ###   ########.fr       */
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
	PIPE,
	IN,
	OUT,
	APP,
	HEREDOC,
}	 e_type;

typedef struct	s_token
{
	char 			*str;
	int				type;
	char			*dir; //FREED
	int				connected;
	int				distanced;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//cmd, args, input, output, args_exec: freed
typedef struct s_command
{
	t_token				*cmd;		//command
	t_token				*args;		//arguments
	t_token				*input;		//< / heredoc
	t_token				*output;	//> / append
	int					arg_num;
	int					pid;
	char				**args_exec;
	struct s_command	*next;
}	 t_command;

//env & s_env: freed
typedef struct s_env
{
	char			*var; //previously str
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	int		read;
	int		write;
}	t_pipe;

//mod_env, built_ins, pipe, heredoc, commands, env, s_env: freed
typedef struct	s_bigshell
{
	int			num_cmd;
	//int			exit_stat; storing exit stat in env
	int			simple_error; //this will be set with stdlib macros to define whether I need to exit the minishell
	int			pipe_fd[2];
	int			pipe_fd2[2]; //possibly not necesary
	int			var_i;	//counts how many variables exist in the environment
	int			reference_i; //keeps count of data->env
	int			std_in; //stored std_in
	int			std_out; //stored std_out
	int			fd_in; //redirected in
	int			fd_out; //redirected out
	int			heredoc_fd; //redirected err
	int			redir;
//	char		*export_var; //tf is this
//	char		**og_env; //do I use u?
	char		**mod_env;
	char		**built_ins; //FREED
	t_pipe		*pipe;
	t_token		*heredoc;	//token with delimiter and str;
	t_command	*commands; //
	t_env		*env; //FREED
	t_env		*s_env; //FREED
}	t_bigshell;


typedef struct s_signal
{
	int			sigint;
	int			sigquit;
	int			pid;
	t_bigshell *data;
}	t_sig;

extern int    g_sig;

void	restore_fork(t_bigshell *data, int mode);
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
void	exit_child(t_bigshell *data, int exit_stat);
void	CRITICAL_FAILURE(t_bigshell *data, char *str);

void	simple_exec(t_bigshell *data);

void    restore_output(t_bigshell *data);

void	complex_exec(t_bigshell *data);
void	pipe_init(t_bigshell *data);

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
int		get_exitcode(t_bigshell *data);

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
