#ifndef SIG_H
# define SIG_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "../../minishell.h"
# include "../parser/parse.h"
//# define _XOPEN_SOURCE 700
//# define _DEFAULT_SOURCE

void	handler(int sig);
void    sig_init(t_bigshell *data, void *handler);
int	    check_sigs();
extern t_sig    g_sig;
#endif