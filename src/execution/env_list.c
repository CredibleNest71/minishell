/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a <a@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:46:40 by a                 #+#    #+#             */
/*   Updated: 2024/02/17 08:35:57 by a                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env   *create_node(t_bigshell *data, char *str)
{
    t_env   *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        // handle critical failure
    new_node->str = ft_strdup(str);
    if (!new_node->str)
        fatal_error(data, 1);
    new_node->next = NULL;
    return (new_node);
}

void    store_env(t_bigshell *data, char **env)
{
    int     i;
    t_env   *current_node;

    i = 0;
    data->env = create_node(data, env[i]);
    current_node = data->env;
    while (env[++i])
    {
        current_node->next = create_node(data, env[i]);
        current_node = current_node->next; 
    }
    data->var_i = i; //this should be updated every time export adds a variable to the list
}

void    convert_env(t_bigshell *data)
{
    int i;
    
    data->mod_env = (char **)malloc(sizeof(char *) * data->var_i);
    if (!data->mod_env)
        fatal_error(data, 1);
    data->mod_env[data->var_i] = NULL;
    i = -1;
    while (data->mod_env[++i])
    {
        data->mod_env[i] = ft_strdup(data->env->str);
        if (!data->mod_env[i])
            fatal_error(data, 1);
    }
}

// void print_env_list(t_bigshell *data)
// {
//     t_env *current = data->env;
//     while (current != NULL)
//     {
//         printf("%s\n", current->str);
//         current = current->next;
//     }
// }

// int main()
// {
//     t_bigshell data;
//     char *env[] = {"STRING1", "STRING2", "STRING3"};

//     // Store environment strings in the linked list
//     store_env(&data, env);

//     // Print the linked list
//     print_env_list(&data);

//     return (0);
// }
