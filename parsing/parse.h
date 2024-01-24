#ifndef PARSE_H
# define PARSE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int	is_seperator(char *str);
t_token	*tokenify(char *str);

#endif