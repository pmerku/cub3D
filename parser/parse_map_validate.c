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

#include <ft_string.h>
#include <ft_memory.h>
#include "utils.h"
#include "cub3d.h"

/**
 * Set spawn coordinates and rotation for player
 * @param win global game structure
 * @param row current row in map
 * @param index index of current row in map
 */
static void	map_spawn_pos(t_win *win, const char *row, int index) {
	int col = 0;
	for (; row[col]; col++) {
		if (row[col] == 'N' || row[col] == 'S') {
			win->pos.dir_x = (row[col] == 'N') ? -1 : 1;
			win->pos.plane_y = (row[col] == 'N') ? 0.66 : -0.66;
			break;
		}
		else if (row[col] == 'E' || row[col] == 'W') {
			win->pos.dir_y = (row[col] == 'W') ? -1 : 1;
			win->pos.plane_x = (row[col] == 'W') ? -0.66 : 0.66;
			break;
		}
	}
	win->pos.x = col + 0.5;
	win->pos.y = index + 0.5;
}

/**
 * Check if special characters have their texture file loaded
 * @param map pointer to the map
 * @param x coordinate x in map
 * @param y coordinate y in map
 */
static void	extra_check(char **map, int *x, int *y) {
	while (map[*y] && map[*y][*x] == 16)
		(*y)++;
	if (map[*y] != NULL)
		close_error("Invalid element after map\n");
	(*y)--;
}

/**
 * Test if all characters are part of the map char set
 * @param map pointer to the map
 * @param win global game structure
 */
static void	map_char_check(char **map, t_win *win) {
	for (int y = 0; map[y]; y++) {
		for (int x = 0; map[y][x] && map[y]; x++) {
			if (!ft_strchr(CHAR_SET, map[y][x]) && map[y][x] != 16)
				close_error("Unsupported character in map\n");
			else if ((win->tex[DOOR_H].wall == NULL && map[y][x] == 'H') || (win->tex[DOOR].wall == NULL && map[y][x] == 'D'))
				close_error("Missing textures\n");
			else if (ft_strchr(SPAWN_SET, map[y][x])) {
				if (win->pos.x == 0 && win->pos.y == 0)
					map_spawn_pos(win, map[y], y);
				else
					close_error("Too many spawn points\n");
			}
			else if (map[y][x] == 16 && map[y])
				extra_check(map, &x, &y);
		}
	}
	if (win->pos.x == 0 && win->pos.y == 0)
		close_error("Invalid spawn\n");
}

/**
 * Algorithm to validate if the map is enclosed
 * @param win global game structure
 * @param map pointer to the map
 * @param x starting position x
 * @param y starting position y
 */
static void	flood_fill(t_win *win, char **map, int x, int y) {
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

/**
 * Check if map characters are valid and mark "empty" tiles
 * @param win global game structure
 */
void		map_validate(t_win *win) {
	map_char_check(win->map.map, win);
	char **map_dup = ft_calloc(win->map.map_h + 1, sizeof(char*));
	malloc_check(map_dup);
	for (int y = 0; y < win->map.map_h; y++) {
		map_dup[y] = ft_strdup(win->map.map[y]);
		malloc_check(map_dup[y]);
		for (int x = 0; map_dup[y][x]; x++) {
			if (ft_strchr(FLOOD, map_dup[y][x]))
				map_dup[y][x] = '$';
		}
	}
	flood_fill(win, map_dup, (int)win->pos.x, (int)win->pos.y);
	delete_data(map_dup);
}
