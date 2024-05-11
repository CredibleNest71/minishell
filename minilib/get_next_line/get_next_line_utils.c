/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischmutz <ischmutz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:15:54 by ischmutz          #+#    #+#             */
/*   Updated: 2023/10/30 15:47:29 by ischmutz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
	{
		i++;
	}
	return (i);
}

size_t	linlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (s[0] == '\n')
		return (1);
	while (s[i] != '\n' && s[i])
	{
		i++;
		if (s[i] == '\n')
			return (i + 1);
	}
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int		i;
	char	c_;
	char	*result;
	char	*s_;

	i = 0;
	result = NULL;
	s_ = (char *) s;
	c_ = (char) c;
	while (s_[i] != '\0' || c_ == '\0')
	{
		if (s_[i] != c_)
			i++;
		else
		{
			result = s_ + i;
			break ;
		}
	}
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;

	i = 0;
	if (!s || !s[0])
		return (NULL);
	if (start >= ft_strlen_gnl(s) || len == 0)
	{
		subs = ft_calloc_gnl(1, sizeof(char));
		if (subs == NULL)
			return (NULL);
		return (subs);
	}
	if (len > ft_strlen_gnl(s + start))
		len = ft_strlen_gnl(s + start);
	subs = ft_calloc_gnl(len + 1, sizeof(char));
	if (subs == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t		papamericano;
	char		*str;
	size_t		i;
	size_t		e;

	i = 0;
	e = 0;
	papamericano = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = ft_calloc_gnl(papamericano + 1, sizeof(char));
	if (str == NULL)
		return (liberator(&s1), liberator(&s2), NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[e] != '\0')
	{
		str[i] = s2[e];
		e++;
		i++;
	}
	str[i] = '\0';
	return (liberator(&s1), str);
}

/* char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*str;
	size_t		i;
	size_t		e;
	
	i = 0;
	if (s1 == NULL)
	{
		s1 = (char *)ft_calloc_gnl(1, sizeof(char));
		if (s1 == NULL)
			return (liberator(s1), liberator(s2), NULL);
		s1[0] = '\0';
	}
	// printf("S1: %s\n", s2);
	str = ft_calloc_gnl(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1, sizeof(char));
	if (str == NULL)
		return (liberator(s1), liberator(s2), NULL);
	while (s1[i] != '\0' && ft_strlen_gnl(s1) > i)
	{
		str[i] = s1[i];
		i++;
	}
	e = 0;
	while (s2[e] != '\0' && ft_strlen_gnl(s2) > e)
	{
		str[i] = s2[e];
		i++;
		e++;
	}
	str[i] = '\0';
	return (liberator(s1), str);
} */

/* char	*ft_strjoin_gnl(char *s1, char *s2, int bytes_read, int *progress)
{
	size_t		papamericano;
	char		*str;
	size_t		i;
	size_t		e;
	
	i = 0;
	e = 0;
	papamericano = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	if (s1 == NULL)
		return (*s2);
	// printf("S1: %s\n", s2);
	str = ft_calloc_gnl(papamericano + 1, sizeof(char));
	if (str == NULL)
		return (liberator(s1), liberator(s2), NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[e] != '\0')
	{
		str[i] = s2[e];
		e++;
		i++;
	}
	str[i] = '\0';
	return (liberator(s1), str);
} */
/* char	*ft_strjoin_gnl(char *s1, char *s2, int bytes_read, int *progress)
{
	char		*str;
	size_t		i;
	size_t		e;
	
	i = 0;
	if (s1 == NULL)
		return (*s2);
	// printf("S1: %s\n", s2);
	str = ft_calloc_gnl( + bytes_read + 1, sizeof(char));
	if (str == NULL)
		return (liberator(s1), liberator(s2), NULL);
	while (s2[i] != '\0' && ft_strlen_gnl(s1) > i)
	{
		str[*progress] = s1[i];
		i++;
		*progress += 1;
	}
	str[i] = '\0';
	return (liberator(s1), str);
} */

//#include <stdio.h>
/*int	main(void)
{
	char	*fuck;
	char	*you;
	char	*conjoinedtwins;

	fuck = "goodbye";
	you = "zulu";
	conjoinedtwins = ft_strjoin_gnl(fuck, you);
	printf("%s", conjoinedtwins);
	
} */