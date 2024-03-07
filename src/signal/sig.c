#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <signal.h>
#include "../../minishell.h"
#include "../libft/libft.h"

void	handler(int sig, siginfo_t *info, void *v)
{
    if (sig == SIGINT)
        g_sig.sigint = 1;
    else if (sig == SIGQUIT)
        g_sig.sigquit = 1;
}

void    sig_init(t_bigshell *data)
{
    ft_bzero(&g_sig, sizeof(g_sig));
    if (data)
        g_sig.data = data;
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