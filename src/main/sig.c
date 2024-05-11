/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:17:53 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 13:37:44 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700
#define _DEFAULT_SOURCE
#include <unistd.h>
#include <signal.h>
#include "../../minishell.h"
#include "sig.h"
#include <sys/ioctl.h>
#include <asm/termbits.h>

int	g_sig;

void	reset_sig(int sig)
{
	sig++;
	g_sig = 0;
}

static void	redo_rl(int sig)
{
	sig++;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	set_global(int sig)
{
	g_sig = sig;
}

static void	newline_to_readline(int sig)
{
	if (sig == SIGINT)
	{
		ioctl(0, TIOCSTI, "\n");
		g_sig = SIGINT;
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	set_signals(int mode)
{
	g_sig = 0;
	if (!mode)
	{
		signal(SIGINT, &redo_rl);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 1)
	{
		signal(SIGINT, &set_global);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, &newline_to_readline);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 3)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}
