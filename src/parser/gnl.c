#include "parse.h"
#include "../../minishell.h"
#include "../../libft/libft.h"

static int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*bigify(char *old, int size)
{
	int	i;
	int	newlength;
	char	*new;
	
	newlength = len(old) + size + 1;
	i = 0;
	new = (char *) malloc(newlength);
	while(i < newlength)
		new[i++] = 0;
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	return(new);
}

static void	append(char *dst, char *src, int size)
{
	int	i;
	int	length;

	length = len(dst);
	i = 0;
	while (src[i] && i <= size)
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = 0;
}

static void	set_rest(char *rest, int bookmark)
{
	int		i;
	char	temp[10 + 1] = {0};
	
	i = 0;
	bookmark++;
	while(bookmark < 10)
	{
		temp[i++] = rest[bookmark++];
	}
	i = 0;
	while (i < 10)
	{
		rest[i] = temp[i];
		i++;
	}
}

static int	get_buf(int fd, char *rest)
{
	char	buf[10];
	int		bytesread;
    int     i;

    i = 0;
	bytesread = read(fd, buf, 10);
	if (bytesread <= 0)
		return (0);
    while (i < 10)
    {
        rest[i] = buf[i];
        i++;
    }
	return (i);
}

static int		check_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
    return (i);
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[10] = {0};
	int			bookmark;
    int         found;
	int			i;

	found = 0;
	i = 0;
	line = (char *) malloc(10);
	i = 0;
	if (!line || fd <= 0)
	{
		free(line);
		return (0);
	}
	while (i < 10)
		line[i++] = 0;

	while (rest[i])
	{
		line = bigify(line, check_buf(rest));
		line[i] = rest[i];
		if (rest[i] == '\n' || (rest[i] == 0 && i < 10))
		{
			set_rest(rest, i);
			return (line);
		}
		i++;
	}
	while (!found)
    {
		if (get_buf(fd, rest) <= 0)
			return (line);
        bookmark = check_buf(rest);
		if (bookmark < 10)
			found = 1;
		line = bigify(line, bookmark + 1);
        append(line, rest, bookmark);
        set_rest(rest, bookmark);
    }
	return (line);
}
