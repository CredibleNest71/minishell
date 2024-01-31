#ifndef PARSE_H
# define PARSE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int			is_char(char c, char *chars);
int			is_seperator(char *str);
t_token	    *tokenify(char *str);
int         count_elements(char *);
char        **token_splitter(char *str);
t_command	**commandlistmaker(char *str);
#endif