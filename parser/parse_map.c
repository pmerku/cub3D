/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:27:59 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/29 10:01:48 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <cub3d.h>

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
** @param  t_win *win   allocated global window structure
** @param  int   *i     reference to index position
** @return void
*/

void	parse_map(char **data, t_win *win)
{
	int		pos;
	int		i;
	int 	j;

	pos = 0;
	while (data[pos])
		pos++;
	win->map.map_h = pos;
	win->map.map = (char**)malloc(sizeof(char*) * (pos + 1));
	malloc_check(win->map.map);
	pos = 0;
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
