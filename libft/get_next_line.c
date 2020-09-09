/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:50:43 by prmerku           #+#    #+#             */
/*   Updated: 2019/12/07 18:50:43 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <libft.h>

/*
** Modified version
*/

static char	*ft_strdup_gnl(const char *s1, int *res)
{
	size_t	len;
	void	*mem;

	if (!s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	mem = (char*)malloc(len + 1);
	if (!mem)
	{
		*res = -1;
		return (NULL);
	}
	ft_memcpy(mem, s1, len + 1);
	return (mem);
}

/*
** Modified version
*/

static char	*ft_strjoin_gnl(char const *s1, char const *s2, int *res)
{
	char	*str;
	size_t	len_1;
	size_t	len_2;

	if (!s1 || !s2)
	{
		*res = -1;
		return (NULL);
	}
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = malloc(len_1 + len_2 + 1);
	if (!str)
	{
		*res = -1;
		return (NULL);
	}
	ft_strlcpy(str, s1, len_1 + 1);
	ft_strlcat(str, s2, len_1 + len_2 + 1);
	return (str);
}

/*
** Get next line sub fucntion.
** Reading the buffer and storing the result of the read in the static char. If
** the static char already exists this function will join the previous reading
** with the current read buffer.
** The return values of the function are:
**		tmp_res > 0  "The last position of the read byte"
**		tmp_res == 0 "EOF reached"
**		tmp_res < 0  "An error occured while reading"
*/

static int	ft_read(const int fd, char *fd_store[fd], int x)
{
	char	*buf;
	char	*tmp;
	int		tmp_res;

	buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	tmp_res = read(fd, buf, BUFFER_SIZE);
	if (tmp_res >= 0 && x != -1)
		buf[tmp_res] = '\0';
	if (fd_store[fd] == NULL && tmp_res > 0 && x != -1)
		fd_store[fd] = ft_strdup_gnl(buf, &tmp_res);
	else if (tmp_res > 0 && x != -1)
	{
		tmp = fd_store[fd];
		fd_store[fd] = ft_strjoin_gnl(tmp, buf, &tmp_res);
		free(tmp);
	}
	free(buf);
	if ((tmp_res == -1 && fd_store[fd]) || (x == -1 && fd_store[fd]))
	{
		free(fd_store[fd]);
		fd_store[fd] = NULL;
	}
	return ((x == -1) ? -1 : tmp_res);
}

/*
** The get_next_line() function returns a line read from a file descriptor
** without the newline. Calling the function in a loop will allow to read
** the entire text available on a file descriptor one line at a time until EOF.
**
** The return values of the function are:
** 		1  "a line has been read"
**		0  "EOF has been reached"
**	   -1  "an error has occured"
**
** This get_next_line implementation works with multiple file descriptors
** simultaneously.
*/

int			get_next_line(int fd, char **line)
{
	static char	*fd_store[2];
	char		*ptr_nl;
	char		*tmp;
	int			res;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	res = 1;
	while (!ft_strchr(fd_store[fd], '\n') && res > 0)
		res = ft_read(fd, fd_store, res);
	if (res < 0)
		return (-1);
	ptr_nl = ft_strchr(fd_store[fd], '\n');
	if (ptr_nl != NULL)
	{
		*line = ft_substr(fd_store[fd], 0, ptr_nl - fd_store[fd]);
		tmp = fd_store[fd];
		fd_store[fd] = ft_strdup_gnl(ptr_nl + 1, &res);
		free(tmp);
		return ((*line == NULL || res < 0) ? ft_read(fd, fd_store, -1) : 1);
	}
	*line = ft_strdup_gnl(fd_store[fd], &res);
	free(fd_store[fd]);
	fd_store[fd] = NULL;
	return ((*line == NULL || res < 0) ? -1 : 0);
}
