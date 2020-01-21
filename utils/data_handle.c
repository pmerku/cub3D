/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:36:22 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/21 11:37:24 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

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
			close_error(1);
		buf[res] = '\0';
		tmp = map;
		map = (tmp == NULL) ? ft_strdup(buf) : ft_strjoin(tmp, buf);
		free(tmp);
		if (!map)
			close_error(2);
	}
	data = ft_split(map, '\n');
	free(map);
	return (data);
}
