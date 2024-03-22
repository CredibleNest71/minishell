#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <signal.h>
#include "../../minishell.h"
#include "../../libft/libft.h"
#include "sig.h"

void	handler(int sig/*, siginfo_t *info, void *v*/)
{
	write(1, "SIGNAL RECEIVED", 17);
	if (sig == SIGINT)
		g_sig.sigint = 1;
	else if (sig == SIGQUIT)
		g_sig.sigquit = 1;
}

int	check_sigs()
{
	return (g_sig.sigint + g_sig.sigquit * 10);
}

void sig_init(t_bigshell *data, void *handler)
{
	ft_bzero(&g_sig, sizeof(g_sig));
	if (data)
		g_sig.data = data;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
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