/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:16:55 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 11:17:15 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "../../minishell.h"
# include "../parser/parse.h"

extern int		g_sig;
void			handler(int sig);
void			sig_init(t_bigshell *data, void *handler);
void			set_signals(int mode);
int				check_sigs(void);
#endif