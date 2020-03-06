/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_validate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 10:23:08 by prmerku           #+#    #+#             */
/*   Updated: 2020/03/04 11:02:14 by prmerku       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <libft.h>
#include <cub3d.h>

/*
** Parse the string and set spawn point for the player with correct rotation
**
** @param  t_win      *win allocated global window structure
** @param  const char *row passed string to loop over
** @return void
*/

static void	map_spawn_pos(t_win *win, const char *row, int index)
{
	int		col;

	col = 0;
	while (row[col])
	{
		if (row[col] == 'N' || row[col] == 'S')
		{
			win->pos.dir_x = (row[col] == 'N') ? -1 : 1;
			win->pos.plane_y = (row[col] == 'N') ? 0.66 : -0.66;
			break ;
		}
		else if (row[col] == 'E' || row[col] == 'W')
		{
			win->pos.dir_y = (row[col] == 'W') ? -1 : 1;
			win->pos.plane_x = (row[col] == 'W') ? -0.66 : 0.66;
			break ;
		}
		col++;
	}
	win->pos.x = col + 0.5;
	win->pos.y = index + 0.5;
}

/*
** Check if extra character has texture loaded
**
** @param  t_win  *win allocated global window structure
** @param  int       c position character
** @return void
*/

static void	extra_check(char **map, int *x, int *y)
{
	while (map[*y] && map[*y][*x] == 16)
		(*y)++;
	if (map[*y] != NULL)
		close_error("Invalid element after map\n");
	(*y)--;
}

/*
** Parse the 2D array and check for unsupported characters.
** If a supported character is found skip it or set spawn point for player.
**
** @param  char  **map allocated 2D array to parse
** @param  t_win  *win allocated global window structure
** @return void
*/

static void	map_char_check(char **map, t_win *win, int y, int x)
{
	while (map[y])
	{
		x = 0;
		while (map[y][x] && map[y])
		{
			if (!ft_strchr(CHAR_SET, map[y][x]) && map[y][x] != 16)
				close_error("Unsupported character in map\n");
			else if ((win->tex[DOOR_H].wall == NULL && map[y][x] == 'H')
				|| (win->tex[DOOR].wall == NULL && map[y][x] == 'D'))
				close_error("Missing textures\n");
			else if (ft_strchr(SPAWN_SET, map[y][x]))
			{
				if (win->pos.x == 0 && win->pos.y == 0)
					map_spawn_pos(win, map[y], y);
				else
					close_error("Too many spawn points\n");
			}
			else if (map[y][x] == 16 && map[y])
				extra_check(map, &x, &y);
			x++;
		}
		y++;
	}
	if (win->pos.x == 0 && win->pos.y == 0)
		close_error("Invalid spawn\n");
}

/*
** Validate map algorithm
**
** @param  t_win *win allocated global window structure
** @param  int      x position x in map
** @param  int      y position y in map
** @return void
*/

static void	flood_fill(t_win *win, char **map, int x, int y)
{
	if (y < 0 || x < 0 || y > win->map.map_h - 1 || map[y][x] == '\0'
		|| map[y][x] == ' ')
		close_error("Invalid map\n");
	if (map[y][x] == '1' || map[y][x] == '0')
		return ;
	if (map[y][x] != '$')
		return ;
	if (map[y][x] == '$')
		map[y][x] = '0';
	flood_fill(win, map, x + 1, y);
	flood_fill(win, map, x - 1, y);
	flood_fill(win, map, x, y + 1);
	flood_fill(win, map, x, y - 1);
	flood_fill(win, map, x - 1, y - 1);
	flood_fill(win, map, x + 1, y + 1);
	flood_fill(win, map, x + 1, y - 1);
	flood_fill(win, map, x - 1, y + 1);
}

/*
** Calling function for map validation and transform "empty" tile to target
** for the flood fill algorithm
**
** @param  t_win *win allocated global window structure
** @return void
*/

void		map_validate(t_win *win)
{
	int		x;
	int		y;
	char	**map_dup;

	map_char_check(win->map.map, win, 0, 0);
	map_dup = ft_calloc(win->map.map_h + 1, sizeof(char*));
	malloc_check(map_dup);
	y = 0;
	while (y < win->map.map_h)
	{
		x = 0;
		map_dup[y] = ft_strdup(win->map.map[y]);
		malloc_check(map_dup[y]);
		while (map_dup[y][x])
		{
			if (ft_strchr(FLOOD, map_dup[y][x]))
				map_dup[y][x] = '$';
			x++;
		}
		y++;
	}
	flood_fill(win, map_dup, (int)win->pos.x, (int)win->pos.y);
	delete_data(map_dup);
}
