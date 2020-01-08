/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:32 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/08 18:12:36 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <cub3d.h>

static void	parse_info(char *buf, t_win *win)
{
	parse_resolution(buf, win);
	//parse_color
	//parse_texture
	//parse_sprite
}

static void	parse_map(char *map, t_win *win)
{
	win->map = ft_split(map, '\n');
	printf("%c\n", win->map[0][70]);
}

void	parse_file(char *s, t_win *win)
{
	char *buf;
	char *map;
	int res;
	int fd;

	if (ft_strnstr(s, ".cub", ft_strlen(s)) == NULL)
		close_error(0);
	fd = open(s, O_RDONLY);
	if (fd < 0)
		close_error(1);
	res = 1;
	map = NULL;
	while (res > 0)
	{
		res = get_next_line(fd, &buf);
		if (buf[0] == '1')
			map = (map == NULL) ? ft_strdup(buf) : ft_strjoin(map, buf);
		else
			parse_info(buf, win);
		free(buf);
	}
	parse_map(map, win);
	free(map);
}