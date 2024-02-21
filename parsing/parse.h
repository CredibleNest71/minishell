#ifndef PARSE_H
# define PARSE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

//classifier
void	    classify(t_token *list);
void	    mark_commands(t_token *list);
void	    clean_token(t_token *token);
t_command   *transform(t_token *list);


//extras
char    	*ft_strndup(const char *s, int n);
int			is_char(char c, char *chars);
int			is_seperator(char *str);
t_token	    *ft_tokenlast(t_token *lst);
t_token     *token_dup(t_token *token);
void	    token_append(t_token *lst, t_token *token);

//tokenv1
t_token	    *tokenify(char *str);
int         count_elements(char *);
char        **token_splitter(char *str);
t_command	**commandlistmaker(char *str);

//expander
char *expand(char *str);

#endif