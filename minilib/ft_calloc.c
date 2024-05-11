/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:16:36 by mresch            #+#    #+#             */
/*   Updated: 2023/09/07 16:51:00 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*assign;
	void	*ans;
	size_t	i;

	i = 0;
	if (nmemb * size == 0)
		return (malloc (0));
	if ((nmemb * size) / size != nmemb)
		return (0);
	ans = malloc(size * nmemb);
	if (ans == 0)
		return (0);
	assign = (char *) ans;
	while (i < nmemb * size)
		assign[i++] = 0;
	return (ans);
}
