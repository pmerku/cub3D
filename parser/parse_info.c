/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/23 14:28:00 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <utils.h>
#include <parser.h>

/*
** Parse the 2D array and save the resolution separately in the
** global window struct
**
** @param  char  **data allocated 2D array to parse
** @param  t_win *win   allocated global window structure
** @param  int   *i     reference to index position
** @return void
*/

void		parse_resolution(char **data, t_win *win, int *i)
{
	char	**s;

	s = ft_split(data[*i], ' ');
	if (!(*s))
		close_error("Malloc error\n");
	win->x = ft_atoi(s[1]);
	win->y = ft_atoi(s[2]);
	delete_data(s);
}

/*
** Parse the 2D array and save the sprite separately in the global window struct
**
** @param  char  **data allocated 2D array to parse
** @param  t_win *win   allocated global window structure
** @param  int   *i     reference to index position
** @return void
*/

void		parse_sprite(void)
{
}

/*
** Parse the 2D array and save the colors separately in the global window struct
**
** @param  char  **data allocated 2D array to parse
** @param  t_win *win   allocated global window structure
** @param  int   *i     reference to index position
** @return void
*/

static void	parse_argb(char **data, t_win *win, int *i)
{
	char	**s;

	while (ft_strchr(data[*i], ','))
		(*(char *)ft_strchr(data[*i], ',')) = ' ';
	s = ft_split(data[*i], ' ');
	if (!(*s))
		close_error("Malloc error\n");
	win->tex.r = ft_atoi(s[1]);
	win->tex.g = ft_atoi(s[2]);
	win->tex.b = ft_atoi(s[3]);
	if (win->tex.r > 255 || win->tex.g > 255 || win->tex.b > 255)
		close_error("Incorrect ARGB numbers\n");
	if (data[*i][0] == 'F')
		win->tex.f_color = win->tex.a << 24 | win->tex.r << 16 |
				win->tex.g << 8 | win->tex.b;
	if (data[*i][0] == 'C')
		win->tex.c_color = win->tex.a << 24 | win->tex.r << 16 |
				win->tex.g << 8 | win->tex.b;
	delete_data(s);
}

/*
** Parse the 2D array and save the textures separately in the global
** window struct
**
** @param  char  **data allocated 2D array to parse
** @param  t_win *win   allocated global window structure
** @param  int   *i     reference to index position
** @return void
*/

void		parse_texture(char **data, t_win *win, int *i)
{
	if (data[*i][0] == 'F' || data[*i][0] == 'C')
		parse_argb(data, win, i);
	else if ((*(u_int16_t*)data[*i]) == (*(u_int16_t*)"NO"))
		parse_nw(data, win, i);
	else if ((*(u_int16_t*)data[*i]) == (*(u_int16_t*)"SO"))
		parse_sw(data, win, i);
	else if ((*(u_int16_t*)data[*i]) == (*(u_int16_t*)"WE"))
		parse_ww(data, win, i);
	else if ((*(u_int16_t*)data[*i]) == (*(u_int16_t*)"EA"))
		parse_ew(data, win, i);
}
