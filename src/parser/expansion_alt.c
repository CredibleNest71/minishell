/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_alt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:55:07 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 19:57:41 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "parse.h"

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

char	*append_to_final(char *final, char *var_ptr, \
		t_ptr_pair ptr, t_bigshell *data)
{
	char	*val;
	char	*var;
	int		v;

	v = 0;
	var = find_var_name(var_ptr);
	val = get_val(var, data);
	if (!val)
	{
		*ptr.i += ft_strlen(var) + 1;
		free(var);
		return (final);
	}
	ft_strlcpy(final, val, ft_strlen(val) + 10);
	*ptr.j += ft_strlen(val);
	*ptr.i += ft_strlen(var) + 1;
	free(var);
	return (final);
}

static int	get_total_len(char *str, t_bigshell *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
			len += ft_strlen(var2val(&str[i], data));
		i++;
	}
	return (i + len);
}

char	*expand(char *str, t_bigshell *data)
{
	char	*final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (!ft_strchr(str, '$'))
		return (str);
	if (!ft_strcmp(&str[i], "$"))
		return (str);
	final = ft_calloc(get_total_len(str, data), 1);
	while (i < ft_strlen(str) && str[i])
	{
		if (!ft_strcmp(&str[i], "$"))
			final[j++] = str[i++];
		else if (str[i] == '$')
			append_to_final(&final[j], &str[i], (t_ptr_pair){&i, &j}, data);
		else
			final[j++] = str[i++];
	}
	free(str);
	return (final);
}
