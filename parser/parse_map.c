/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:27:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 11:26:26 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <stdlib.h>
#include <cub3d.h>

/*
** Loop over string and return the length of the string without spaces
**
** @param  const char *s passed string
** @return size_t        length of the string
*/

static size_t	line_size(const char *s)
{
	size_t	size;

	size = 0;
	while (*s)
	{
		if (*s != ' ')
			size++;
		s++;
	}
	return (size);
}

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
	int		i;
	int		j;

	while (data[pos])
	{
		i = 0;
		j = 0;
		win->map.map[pos] = ft_malloc(line_size(data[pos]) + 1);
		while (data[pos][j])
		{
			if (data[pos][j] != ' ')
			{
				win->map.map[pos][i] = data[pos][j];
				i++;
			}
			j++;
		}
		win->map.map[pos][i] = '\0';
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
	win->map.map = (char**)malloc(sizeof(char*) * (pos + 1));
	malloc_check(win->map.map);
	map_copy(data, win, 0);
}
