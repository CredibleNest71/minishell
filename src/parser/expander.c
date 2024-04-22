/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:07 by mresch            #+#    #+#             */
/*   Updated: 2024/04/17 15:47:20 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"

char	*ft_string_insert(char *str, char *in, int idx, int varlen)
{
	char	*ret;
	char	*intro;
	char	*outro;
	char	*first;

	if (!str)
		return (NULL);
	intro = NULL;
	if (idx)
		intro = ft_strndup(str, idx);
	outro = ft_strdup(str + idx + varlen + 1);
	first = ft_strjoin(intro, in);
	ret = ft_strjoin(first, outro);
	if (idx)
	{
		free(intro);
		free(first);
	}
	free(outro);
	free(str);
	return (ret);
}

char	*find_var_name(char *str)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_') && str[i + j])
		j++;
	ret = ft_strndup(&str[i], j);
	return (ret);
}

char	*get_val(char *var, t_bigshell *data)
{
	t_env	*curr;
	t_env	*ans;

	ans = NULL;
	if (!data || !var)
		return (NULL);
	curr = data->env;
	while (curr)
	{
		if (!ft_strncmp(curr->var, var, ft_strlen(var) + 1))
			ans = curr;
		curr = curr->next;
	}
	if (!ans)
		return (NULL);
	return (ans->value);
}

//expands $-variable
char	*expand(char *str, t_bigshell *data)
{
	char	*here;
	char	*var;
	char	*val;
	char	*new;

	while (ft_strchr(str, '$'))
	{
		if (!strncmp(str, "$", 2))
			return (str);
		here = ft_strchr(str, '$');
		if (here)
		{
			var = find_var_name(here);
			if (!var)
				return (str);
			val = get_val(var, data);
			if (!val && ft_strlen(var) + 1 == ft_strlen(str))
				return (NULL);
			new = ft_string_insert(str, val, here - str, ft_strlen(var));
			free(var);
			str = new;
		}
	}
	return (str);
}
