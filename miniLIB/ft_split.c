/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mresch <mresch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:13:10 by mresch            #+#    #+#             */
/*   Updated: 2023/09/07 12:13:51 by mresch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Function name ft_split
Prototype char **ft_split(char const *s, char c);
Turn in files -
Parameters s: The string to be split.
c: The delimiter character.
Return value The array of new strings resulting from the split.
NULL if the allocation fails.
External functs. malloc, free
Description Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/

int	count(char const *s, char c)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i] != 0)
			i++;
		if (!s[i])
			break ;
		num++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	return (num);
}

int	search_next(char const *s, int start, char c)
{
	int	i;

	i = 0;
	while (s[start + i] != 0 && s[start + i] != c)
	{
		i++;
	}
	return (start + i);
}

char	*cut(char const *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(end - start + 1);
	if (!word)
		return (0);
	while (start + i < end)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**freedom(char **ret, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		i;
	int		start;
	int		end;

	start = 0;
	i = 0;
	ret = (char **) malloc(sizeof(char *) * (count(s, c) + 1));
	if (!ret)
		return (0);
	ret[count(s, c)] = 0;
	while (i < count(s, c))
	{
		while (s[start] == c)
			start++;
		end = search_next(s, start, c);
		ret[i] = cut(s, start, end);
		if (ret[i] == 0)
			return (freedom(ret, i));
		start = end;
		i++;
	}
	return (ret);
}
/*
int	main(int ac, char **av)
{
	ft_split(av[1], av[2][0]);
	return 0;
}
*/