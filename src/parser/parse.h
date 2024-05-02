/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:54:17 by mresch            #+#    #+#             */
/*   Updated: 2024/05/02 15:30:28 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../../minishell.h"
# define SPACE3 "\n\t\v \r\f"

// //classifier
// void	    classify(t_token *list);
// void	    mark_commands(t_token *list);
// void	    clean_token(t_token *token, t_bigshell *data);
// t_command   *transform(t_token *list, t_bigshell *data);
//extras
char		*ft_strndup(const char *s, int n);
int			is_char(char c, char *chars);
int			is_seperator(char *str);
t_token		*ft_tokenlast(t_token *lst);
t_token		*token_dup(t_token *token);
void		token_append(t_token *lst, t_token *token);
void		skip_white_space(char *str, int *i);
void		skip_chars(char *str, int *i);
int			ft_token_count(t_token **list);

// //tokenv1
// t_token	    *tokenify(char *str);
// int         count_elements(char *);
// char        **token_splitter(char *str);
// t_command	**commandlistmaker(char *str);
//tokenextras
void		delete_token(t_token *token);
void		delete_token_list(t_token *list);
void		delete_command_list(t_command *cmd);
void		token_list_add(t_token **tokenlist, t_token *token);
void		delete_char_array(char **arr);
int			quotes(t_token *token, char *str, int *i, char quote);
int			no_quotes(t_token *token, char *str, int *i);
void		set_type(t_token *token, char *str, int *i);

//tokenv1
void		token_list_add(t_token **tokenlist, t_token *token);
t_token		**tokenmaker(char *str);

//commander
t_command	**commands_finalized(t_token **list, t_bigshell *data);

//expansion
char		*expand(char *str, t_bigshell *data);
char		*get_val(char *var, t_bigshell *data);

//expansion_routine_1
int			expand_no_quotes(t_token **list, \
			t_token *curr, t_bigshell *data);
char		*remove_quotes(char *str);
int			launch_expansion(t_token **list, \
			t_token *curr, t_bigshell *data);
t_token		**expander(t_token **list, t_bigshell *data);

//expansion_routine_2
void		mark_join(t_token **list);
void		join(t_token **list);
int			tilde(t_token *curr, t_bigshell *data);

//expansion_routine_3
t_token		*make_t(char *str);
t_token		**split_to_token(char *expanded, int join);
void		insert_tokenlist(t_token **list, \
			t_token *curr, t_token **addlist);
void		remove_token(t_token *curr);

//parse
t_command	*parse(char *input, t_bigshell *data);
void		print_cmds(t_command *cmd, t_bigshell *data);

//SYNTAX
int			check_syntax(t_bigshell *data, char *str);

#endif