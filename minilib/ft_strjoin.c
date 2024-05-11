/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:54:08 by mresch            #+#    #+#             */
/*   Updated: 2024/05/11 13:23:36 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*ans;

	j = 0;
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ans = malloc(len + 1);
	if (!ans)
		return (0);
	if (s1)
	{
		while (s1[i])
		{
			ans[i] = s1[i];
			i++;
		}
	}
	if (s2)
		while (s2[j])
			ans[i++] = s2[j++];
	ans[i] = 0;
	return (ans);
}
/*
int main(int ac, char **av)
{
	printf("%s", ft_strjoin(av[1], av[2]));
	return 0;
}
*/