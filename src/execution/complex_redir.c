/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:36:15 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/10 18:20:18 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void    redir(t_command *cmd, t_bigshell *data)
{
    if (cmd->input)
    {
        if (cmd->input->type == (enum type) HEREDOC)
            heredoc(cmd, data);
        else
            input_redir(cmd, data);
    }
    if (cmd->output)
    {
        if (cmd->output->type == (enum type) APPEND)
            append_redir(cmd, data);
        else
            output_redir(cmd, data);
    }
} */

void    restore_output(t_bigshell *data)
{
    if (dup2(data->std_out, 1) == -1)
        CRITICAL_FAILURE(data, "restoring stdout: dup2 fail");
}

/* void    complex_redir(t_bigshell *data)
{
    if
} */
