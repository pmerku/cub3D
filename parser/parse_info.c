/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/25 09:48:44 by prmerku          ###   ########.fr       */
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
	win->color.r = ft_atoi(s[1]);
	win->color.g = ft_atoi(s[2]);
	win->color.b = ft_atoi(s[3]);
	if (win->color.r > 255 || win->color.g > 255 || win->color.b > 255)
		close_error("Incorrect ARGB numbers\n");
	if (data[*i][0] == 'F')
		win->color.f_color = win->color.a << 24 | win->color.r << 16 |
				win->color.g << 8 | win->color.b;
	if (data[*i][0] == 'C')
		win->color.c_color = win->color.a << 24 | win->color.r << 16 |
				win->color.g << 8 | win->color.b;
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
