#ifndef SIG_H
# define SIG_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "../../minishell.h"
# include "../parser/parse.h"

void			handler(int sig);
void			sig_init(t_bigshell *data, void *handler);
void			set_signals(int mode);
int				check_sigs();
extern int		g_sig;
#endif