/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:04:24 by ischmutz          #+#    #+#             */
/*   Updated: 2024/03/13 11:02:00 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//frees the node_to_delete in unset
void	free_single_node(t_bigshell *data, t_env **node)
{
	free((*node)->var);
	free((*node)->value);
	free(*node);
	update_exit_stat(data, 0);
}

//frees env & sorted env linked list (used in export & unset)
void	free_env(t_bigshell *data)
{
	t_env	*tmp;
	if (data->s_env)
	{
		while (data->s_env)
		{
			tmp = data->s_env;
			data->s_env = data->s_env->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
		}
	}
	if (data->env)
	{
		while (data->env)
		{
			tmp = data->env;
			data->env = data->env->next;
			free(tmp->var);
			free(tmp->value);
			free(tmp);
		}
	}
}

void	free_builtin_list(t_bigshell *data)
{
	int	i;

	i = 0;
	if (data->built_ins)
	{
		while (data->built_ins[i])
			free(data->built_ins[i++]);
		free(data->built_ins);
	}
}

void	free_tokens(t_token *data)
{
	if (data->str)
		free(data->str);
	if (data->dir)
		free(data->dir);
}

void	free_commands(t_bigshell *data)
{
	if (data->commands->input)
	{
		free_tokens(data->commands->input);
		free(data->commands->input);
	}
	if (data->commands->output)
	{
		free_tokens(data->commands->output);
		free(data->commands->output);
	}
	if (data->commands->cmd)
	{
		free_tokens(data->commands->cmd);
		free(data->commands->cmd);
	}
	if (data->commands->args)
	{
		free_tokens(data->commands->args);
		free(data->commands->args);
	}
	/* if (data->commands->nexus) //tf is nexus??
	{} */
}

void	free_struct(t_bigshell *data)
{
	//free everything before exiting minishell;
	//puts("Haha i was called");
	free_env(data);
	free_builtin_list(data);
	if (data->commands)
	{
		while (data->commands)
		{
			free_commands(data);
			data->commands = data->commands->next;
		}
		free(data->commands);
	}
}
