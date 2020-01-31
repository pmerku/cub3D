/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:23:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/31 17:44:28 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <libft.h>
#include <engine.h>
#include <cub3d.h>

static size_t	map_h_edge(char *row)
{
	size_t	pos;
	size_t	col;

	pos = 0;
	col = 0;
	while (row[pos])
	{
		if (row[pos] != '1')
			close_error("Invalid map\n");
		if (row[pos] == '1')
			col++;
		pos++;
	}
	return (col);
}

static void		map_spawn_pos(t_win *win, char *row, int index)
{
	int		col;

	col = 0;
	while (*row)
	{
		if (*row == 'N' || *row == 'S')
		{
			win->pos.dir_x = (*row == 'N') ? -1 : 1;
			win->pos.plane_y = (*row == 'N') ? 0.66 : -0.66;
			*row = '0';
			break ;
		}
		else if (*row == 'E' || *row == 'W')
		{
			win->pos.dir_y = (*row == 'W') ? -1 : 1;
			win->pos.plane_x = (*row == 'W') ? -0.66 : 0.66;
			*row = '0';
			break ;
		}
		if (*row != ' ')
			col++;
		row++;
	}
	win->pos.x = col + 0.5;
	win->pos.y = index + 0.5;
}

static void		map_char_check(char **map, t_win *win)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (map[row])
	{
		col = 0;
		while (map[row][col])
		{
			if (ft_strchr(SPAWN_SET, map[row][col]))
			{
				if (win->pos.x == 0 && win->pos.y == 0)
					map_spawn_pos(win, map[row], row);
				else
					close_error("Too many spawn points\n");
			}
			if (!ft_strchr(CHAR_SET, map[row][col]))
				close_error("Unsupported character in map\n");
			col++;
		}
		row++;
	}
}

void			map_validate(t_win *win)
{
	size_t col;
	size_t row;
	size_t pos;

	row = 0;
	while (win->map.map[row])
		row++;
	col = map_h_edge(win->map.map[0]);
	if (row < 3 || col < 3)
		close_error("Invalid map\n");
	win->map.map_w = col;
	pos = 1;
	while (pos < row - 1)
	{
		if (win->map.map[pos][0] != '1' || win->map.map[pos][col - 1] != '1')
			close_error("Invalid map\n");
		pos++;
	}
	if (col != map_h_edge(win->map.map[row - 1]))
		close_error("Invalid map\n");
	map_char_check(win->map.map, win);
}