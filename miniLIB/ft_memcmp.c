/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:08:39 by mresch            #+#    #+#             */
/*   Updated: 2023/09/06 14:05:16 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*mem1;
	unsigned char	*mem2;

	mem1 = (unsigned char *) s1;
	mem2 = (unsigned char *) s2;
	while (n > 0)
	{
		if (*mem1 != *mem2)
			break ;
		n--;
		mem1++;
		mem2++;
	}
	if (n == 0)
		return (0);
	else
		return (*mem1 - *mem2);
}
/*
int main(){
	int i = 87;
	int j = 6368;
	printf("\nog = %d", memcmp( &j, &j, 3));
	printf("\nmine = %d", ft_memcmp(&j, &j, 3));

	return 0;
}
*/