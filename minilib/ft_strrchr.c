/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:52:52 by mresch            #+#    #+#             */
/*   Updated: 2023/09/05 16:25:42 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	search;

	search = (char) c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == search)
			return (s + i);
		i--;
	}
	return (0);
}
/*
#include <unistd.h>
int main()
{
	char test[] = "17 alpacas passen nicht in mein zimmer";
	write(1, ft_strrchr(test, '1'), 10);
	return 0;
}
*/