/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:37:13 by mresch            #+#    #+#             */
/*   Updated: 2023/09/07 16:50:24 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ans;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (start > (unsigned int) ft_strlen(s))
		return (ft_strdup(""));
	if ((size_t) ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ans = malloc(len + 1);
	if (!ans)
		return (0);
	while (s[i] && j < len)
	{
		if (i >= start)
			ans[j++] = s[i];
		i++;
	}
	ans[j] = 0;
	return (ans);
}
