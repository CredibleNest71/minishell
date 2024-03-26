/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:36:21 by mresch            #+#    #+#             */
/*   Updated: 2023/09/07 16:51:48 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;
	unsigned int	i;

	to = (unsigned char *)dest;
	from = (unsigned char *)src;
	if (to == from)
		return (dest);
	if (to > from)
	{
		i = 0;
		while (++i <= n)
			to[n - i] = from[n - i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			to[i] = from[i];
			i++;
		}
	}
	return (dest);
}
