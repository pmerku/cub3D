/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:27:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/21 12:16:02 by prmerku       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <ft_memory.h>
#include "utils.h"
#include "cub3d.h"

/**
 * Copy over map data
 * @param data map to copy
 * @param win global game structure
 */
static void		map_copy(char **data, t_win *win)
{
	int pos = 0;
	while (data[pos]) {
		win->map.map[pos] = ft_strdup(data[pos]);
		malloc_check(win->map.map[pos]);
		pos++;
	}
	win->map.map[pos] = NULL;
}

/**
 * Allocate memory for the map
 * @param data map data
 * @param win global game structure
 */
void			parse_map(char **data, t_win *win) {
	int pos = 0;
	while (data[pos])
		pos++;
	win->map.map_h = pos;
	win->map.map = ft_calloc(pos + 1, sizeof(char*));
	malloc_check(win->map.map);
	map_copy(data, win);
}
