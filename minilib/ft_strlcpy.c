/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:05:18 by mresch            #+#    #+#             */
/*   Updated: 2024/05/01 17:05:59 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	if (!dest || !src)
		return (0);
	while (src[i] && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
/*
int main(){
	char test[] = "testme";
	char	test2[] = "hallo"; 
	if (ft_strlcpy(test, test2, 5) == 5)
		write(1, "erforg", 6);
	int i = 0;
	while (test[i] != 0)
		write(1, &test[i++], 1);
}
*/
