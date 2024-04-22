/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:59:54 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/17 15:46:22 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void    append(t_bigshell *data, t_command *cmd)
{
    int	fd;

    fd = open(cmd->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
        CRITICAL_FAILURE(data, "open append fail");
    if (dup2(fd, 1) == -1)
        CRITICAL_FAILURE(data, "dup2 append fail");
    if (close(fd) == -1)
        CRITICAL_FAILURE(data, "close append fail");
} */

/* void    append(t_bigshell *data, t_command *command)
{
    
}

if (command->output->type == (enum type)APP) */