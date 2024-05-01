/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_alt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:07 by mresch            #+#    #+#             */
/*   Updated: 2024/04/30 12:06:07 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"

// char	*ft_string_insert(char *str, char *in, int idx, int varlen)
// {
// 	char	*ret;
// 	char	*intro;
// 	char	*outro;
// 	char	*first;

// 	if (!str)
// 		return (NULL);
// 	intro = NULL;
// 	if (idx)
// 		intro = ft_strndup(str, idx);
// 	outro = ft_strdup(str + idx + varlen + 1);
// 	first = ft_strjoin(intro, in);
// 	ret = ft_strjoin(first, outro);
// 	if (idx)
// 	{
// 		free(intro);
// 		free(first);
// 	}
// 	free(outro);
// 	free(str);
// 	return (ret);
// }

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
	while (str[i + j] && (ft_isalnum(str[i + j]) || \
			is_char(str[i + j], "_?")) && str[i + j])
		j++;
	ret = ft_strndup(&str[i], j);
	return (ret);
}

char	*ft_string_insert(char *str, char *in, char *here)
{
	int		len;
	char	*ret;
	int		idx;
	char	*var;

	var = find_var_name(here);
	len = ft_strlen(str) + ft_strlen(in) + 1 - ft_strlen(var) + 1;
	ret = ft_calloc(len, 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, here - str + 1);
	idx = ft_strlen(ret);
	ft_strlcpy(&ret[idx], in, ft_strlen(in) + 100);
	idx = ft_strlen(ret);
	ft_strlcpy(&ret[idx], here + ft_strlen(var) + 1, \
		ft_strlen(here + ft_strlen(var)));
	free(var);
	if (!ft_strlen(ret))
	{
		free(ret);
		ret = NULL;
	}
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

char	*var2val(char *here, t_bigshell *data)
{
	char	*var;
	char	*val;

	var = find_var_name(here);
	if (!var)
		return (NULL);
	val = get_val(var, data);
	free(var);
	return (val);
}

//expands $-variable
char	*expand(char *str, t_bigshell *data)
{
	char	*here;
	char	*val;
	char	*new;

	while (ft_strchr(str, '$'))
	{
		if (!strncmp(str, "$", 2))
			return (str);
		here = ft_strchr(str, '$');
		if (here)
		{
			val = var2val(here, data);
			new = ft_string_insert(str, val, here);
			free(str);
			str = new;
		}
	}
	return (str);
}