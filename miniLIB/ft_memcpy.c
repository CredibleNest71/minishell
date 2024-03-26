/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:19:08 by mresch            #+#    #+#             */
/*   Updated: 2023/09/07 16:48:58 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*psrc;
	char		*pdest;
	size_t		i;

	psrc = src;
	pdest = dest;
	i = 0;
	if (!dest || !src)
		return (0);
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
