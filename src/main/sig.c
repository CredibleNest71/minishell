#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <signal.h>
#include "../../minishell.h"
#include "../../libft/libft.h"
#include "sig.h"

int	check_sigs()
{
	return (g_sig.sigint + g_sig.sigquit * 10);
}

void	redo_rl()
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(int mode)
{
	if (!mode)
	{
		signal(SIGINT, &redo_rl);
		signal(SIGQUIT, SIG_IGN);
	}
}

/*
int main()
{
    struct sigaction sa;
    sa.sa_sigaction = &handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}
*/