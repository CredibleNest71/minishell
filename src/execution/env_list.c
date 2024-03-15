/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:46:40 by a                 #+#    #+#             */
/*   Updated: 2024/03/15 16:48:00 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*create_var(t_bigshell *data, char *str)
{
	t_env	*new_node;
	
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		fatal_error(data, 1);
	new_node->var = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_node->var)
		fatal_error(data, 1);
	new_node->var = ft_strdup(str);
	if (!new_node)
		fatal_error(data, 1);
	new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

   /*  new_node->var = ft_strdup(str);
    if (!new_node->var)
        fatal_error(data, 1); */
t_env   *create_node(t_bigshell *data, char *str)
{
    t_env   *new_node;
	char	*separator;
	int		var_len;
	int		value_len;
	
	if (ft_strlen(str) == 1)
		return(create_var(data, str));
	separator = ft_strchr(str, '=');
	if (!separator)
		simple_error(data, 1);
	var_len = separator - str;
	value_len = ft_strlen(separator + 1);
	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
    	fatal_error(data, 1);
	new_node->var = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!new_node->var)
		fatal_error(data, 1);
	ft_memcpy(new_node->var, str, var_len);
	new_node->var[var_len] = '\0';
	
	new_node->value = (char *)malloc(sizeof(char) * (value_len + 1));
	if (!new_node->value)
		fatal_error(data, 1);
	ft_memcpy(new_node->value, separator + 1, value_len);
	new_node->value[value_len] = '\0';
    new_node->next = NULL;
    return (new_node);
}

//this ft stores the initial env given when the executable is 1st ran
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
    data->var_i = i; //this should be updated every time export adds a variable to the list //do I use this shit? 12.03
}

//check smt looks weird
//ft makes data->env into a char ** for execve
void    convert_env(t_bigshell *data)
{
    int		i;
	char	*str;
	t_env	*current;
    
    data->mod_env = (char **)malloc(sizeof(char *) * data->var_i);
    if (!data->mod_env)
        fatal_error(data, 1);
    data->mod_env[data->var_i - 1] = NULL;
    i = 0;
	current = data->env;
    while (current->next)
    {
		str = ft_strjoin(current->var, "=");
		if (!str)
		{
			printf("strjoin failed\n"); //delete later
			simple_error(data, 1);
		}
		str = ft_strjoin(str, current->value);
		if (!str)
		{
			printf("strjoin failed\n"); //delete later
			simple_error(data, 1);
		}
        data->mod_env[i] = ft_strdup(str);
        if (!data->mod_env[i])
            fatal_error(data, 1);
		current = current->next;
		i++;
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
