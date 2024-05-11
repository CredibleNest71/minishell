/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/09/29 13:27:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
    char		*line;
	static int	bookmark = 0;
    static char	rest[BUFFER_SIZE + 1] = {0};
    int			found;
	int			i;

	found = 0;
	i = 0;
	line = (char *) malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	////printf("\nrest=%s\ncurrent=%s\n", rest, line);
	while (!found)
    {
		i = redo_rest(rest, fd, &bookmark);
		//printf("\nrest=%s\ncurrent=%s\n", rest, line);

		if (i < 0)
		{
			free(line);
			return (NULL);
		}
        line = append_from_rest(line, rest, &found, &bookmark);
		if (i == 0)
			return (line);
		//printf("\nrest=%s\ncurrent=%s\n", rest, line);
    }
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		fd3;
	fd2 = open("tests/test.txt", O_RDONLY);
	fd1 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	
	line = get_next_line(fd1);
	//printf("LINE= %s", line);
	free(line);

	line = get_next_line(fd1);
	//printf("LINE= %s",line);	
	free(line);

	line = get_next_line(fd1);
	//printf("LINE= %s", line);
	free(line);

	line = get_next_line(fd1);
	//printf("LINE= %s", line);
	free(line);

	line = get_next_line(fd1);
	//printf("LINE= %s", line);
	free(line);
	
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}