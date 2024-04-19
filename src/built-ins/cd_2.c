/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:25:29 by ischmutz          #+#    #+#             */
/*   Updated: 2024/04/19 17:06:14 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

void    home_dir(t_bigshell *data)
{
    char    *home;

    home = getenv("HOME");
    if (!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        return ;
    }
    overwrite_pwd(data, home);
}

char    *free_NULL(char *str)
{
    if (str)
        free(str);
    return (NULL);
}

/* void    go_back_helper(t_bigshell *data)
{
    data->mod_cwd = delete_tail(data->cwd);
    overwrite_pwd(data, data->mod_cwd);
    chdir(data->mod_cwd);
    free(data->cwd);
} */

/* void    go_back(t_bigshell *data)
{
    data->buffer_size = BUFFER;
    while (1)
    {
        if (data->cwd)
            break ;
        data->cwd = malloc(sizeof(char) * data->buffer_size);
        if (!data->cwd)
        {
            free(data->cwd);
            CRITICAL_FAILURE(data, "cd: malloc failed in cd.c:go_back");
        }
        getcwd(data->cwd, data->buffer_size);
        if (!data->cwd && errno == ERANGE)
        {
            data->cwd = free_NULL(data->cwd);
            data->buffer_size += BUFFER_INCREMENT;
        }
        if (!data->cwd && errno != ERANGE)
        {
            data->cwd = free_NULL(data->cwd);
            simple_error_message(data, "minishell: cd: unable to get current directory\n", 1);
        }
    }
    go_back_helper(data);
} */

/* void    change_dir(t_bigshell *data, char *path)
{
    char    *slash;
    
    slash = NULL;
    if (path[ft_strlen(path) - 1] == '/')
        path[ft_strlen(path) - 1] = '\0';
    while (*path)
    {
        slash = ft_strchr(path, '/');
        if (!slash)
        {
            if (ft_strncmp(path, "..", ft_strlen(path)) == 0)
                go_back(data);
            else if (chdir(path) == -1)
            {
                printf("minishell: cd: %s: No such file or directory\n", path);
                simple_error(data, 1);
            }
        }
        if (ft_strncmp(path, "..", (slash - path)) == 0)
        {
            go_back(data);
            path = slash + 1;
            continue ;
        }
        
        path++;
    }
} */

char    *get_cwd(t_bigshell *data)
{
    data->buffer_size = BUFFER;
    while (1)
    {
        if (data->cwd)
            break ;
        data->cwd = malloc(sizeof(char) * data->buffer_size);
        if (!data->cwd)
        {
            free(data->cwd);
            CRITICAL_FAILURE(data, "cd: malloc failed in cd.c:go_back");
        }
        getcwd(data->cwd, data->buffer_size);
        if (!data->cwd && errno == ERANGE)
        {
            data->cwd = free_NULL(data->cwd);
            data->buffer_size += BUFFER_INCREMENT;
        }
        if (!data->cwd && errno != ERANGE)
        {
            data->cwd = free_NULL(data->cwd);
            simple_error_message(data, "minishell: cd: unable to get current directory\n", 1);
            break ;
        }
    }
    return (data->cwd);
}

void    ft_cd(t_bigshell *data)
{
    t_token *arg;
    char    *cwd;

    cwd = NULL;
    arg = data->commands->args;
    if (data->commands->arg_num > 1)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        update_exit_stat(data, 1);
        return ;
    }
    if (!arg || ft_strncmp(arg->str, "~", ft_strlen(arg->str)) == 0)
       home_dir(data);
    if (arg->str[0] == '/')
    {
        printf("minishell: cd: %s: No such file or directory\n", arg->str);
        update_exit_stat(data, 1);
        return ;
    }
    else
    {
        //change_dir(data, arg->str);
        if (chdir(arg->str) == -1)
        {
            printf("minishell: cd: %s: No such file or directory\n", arg->str);
            update_exit_stat(data, 1);
            return ;
        }
        cwd = get_cwd(data);
        if (!cwd)
        {
            simple_error_message(data, "minishell: cd.c: cwd failed\n", 1);
            return ;
        }
        overwrite_pwd(data, cwd);
    }
}
