/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/10 12:29:12 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <cub3d.h>

void		delete_data(char **data)
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

static void	parse_info(char **data, t_win *win, int *i)
{
	if (data[*i][0] == 'R')
		parse_resolution(data, win, i);
	else if (data[*i][0] == 'S')
		parse_sprite();
	else
		parse_texture(data, win, i);
}

static void	parse_map(char **data, t_map *map, int *i)
{
	int		len;

	len = 0;
	while (data[len])
		len++;
	map->map_y = len;
	map->map_x = ft_strlen(data[*i]);
	map->map = (char**)malloc(sizeof(char*) * (len + 1));
	if (!map->map)
		close_error(2);
	map->map[len] = NULL;
	len = 0;
	while (data[*i] && data[*i][0] == '1')
	{
		map->map[len] = ft_strdup(data[*i]);
		if (!map->map[len])
			close_error(2);
		(*i)++;
		len++;
	}
}

char		**save_data(int fd)
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
		map = (map == NULL) ? ft_strdup(buf) : ft_strjoin(map, buf);
		if (tmp != NULL)
			free(tmp);
		if (!map)
			close_error(2);
	}
	data = ft_split(map, '\n');
	free(map);
	return (data);
}

void		parse_file(char *s, t_win *win)
{
	char	**data;
	int		fd;
	int		i;

	if (ft_strnstr(s, ".cub", ft_strlen(s)) == NULL)
		close_error(0);
	fd = open(s, O_RDONLY);
	data = save_data(fd);
	i = 0;
	while (data[i])
	{
		if (data[i][0] != '1' && data[i])
			parse_info(data, win, &i);
		else
			parse_map(data, &win->map, &i);
		if (!data[i])
			break ;
		i++;
	}
	delete_data(data);
}
