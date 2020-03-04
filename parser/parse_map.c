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

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

/*
** Parse the 2D array and save the map separately in the global window struct
**
** @param  char  **data allocated 2D array to parse
** @param  t_win   *win allocated global window structure
** @param  int      pos starting position index
** @return void
*/

void			map_copy(char **data, t_win *win, int pos)
{
	while (data[pos])
	{
		win->map.map[pos] = ft_strdup(data[pos]);
		pos++;
	}
	win->map.map[pos] = NULL;
}

/*
** Allocate memory for the map
**
** @param  char  **data allocated 2D array to parse
** @param  t_win   *win allocated global window structure
** @return void
*/

void			parse_map(char **data, t_win *win)
{
	int		pos;

	pos = 0;
	while (data[pos])
		pos++;
	win->map.map_h = pos;
	win->map.map = ft_calloc(pos + 1, sizeof(char*));
	malloc_check(win->map.map);
	map_copy(data, win, 0);
}
