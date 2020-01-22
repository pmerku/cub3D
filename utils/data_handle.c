/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:36:22 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/22 10:31:23 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

/*
** Delete 2D array and its indexes
**
** @param  char ** allocated 2D array
** @return void
*/

void	delete_data(char **data)
{
	int		i;

	i = 0;
	while (data[i] != NULL)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

/*
** Read file and separate the lines based on '\n'
**
** @param  int  fd file descriptor to be read
** @return char ** separated single lines from file into a 2D array
*/

char	**save_data(int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	**data;
	char	*map;
	char	*tmp;
	int		res;

	map = NULL;
	res = 1;
	while (res > 0)
	{
		res = read(fd, buf, BUFFER_SIZE);
		if (res < 0)
			close_error("No such file or can't open file\n");
		buf[res] = '\0';
		tmp = map;
		map = (tmp == NULL) ? ft_strdup(buf) : ft_strjoin(tmp, buf);
		free(tmp);
		if (!map)
			close_error("Malloc error\n");
	}
	data = ft_split(map, '\n');
	free(map);
	return (data);
}
