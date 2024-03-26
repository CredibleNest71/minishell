/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:38:36 by mresch            #+#    #+#             */
/*   Updated: 2023/09/07 11:22:32 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	search;

	search = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == search)
			return (s + i);
		i++;
	}
	if (s[i] == '\0' && search == '\0')
		return (s + i);
	return (0);
}
/*
#include <unistd.h>
int main()
{
	char test[] = "17 alpacas passen nicht in mein zimmer";
	write(1, ft_strchr(test, 'y'), 10);
	return 0;
}
*/