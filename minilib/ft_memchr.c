/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:54:54 by mresch            #+#    #+#             */
/*   Updated: 2024/04/11 11:22:20 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*p;
	unsigned char		search;

	if (!s)
		return (0);
	i = 0;
	search = (unsigned char) c;
	p = (unsigned char *) s;
	while (i < n)
	{
		if (p[i] == search)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
int main()
{
	char test[] = "5 Affen sind einer zu viel";
	write(1,(char *) ft_memchr(test, 'e', 30),10 );
	printf("%s", (char *) ft_memchr(test, 'e', 30));	
	return 0;
}
*/