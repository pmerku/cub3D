/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:56 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/06 11:03:04 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <utils.h>

/*
** Parse the 2D array and save the resolution separately in the
** global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win   allocated global window structure
** @return void
*/

void	parse_resolution(char *data, t_win *win)
{
	char	**s;

	s = ft_split(data, ' ');
	malloc_check(s);
	win->x = ft_atoi(s[1]);
	win->y = ft_atoi(s[2]);
	win->x = (win->x > 2560) ? 2560 : win->x;
	win->y = (win->y > 1440) ? 1440 : win->y;
	win->x = (win->x < 250) ? 250 : win->x;
	win->y = (win->y < 250) ? 250 : win->y;
	delete_data(s);
}

/*
** Parse the 2D array and save the colors separately in the global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win allocated global window structure
** @return void
*/

void	parse_argb(char *data, t_win *win)
{
	char	**s;

	while (ft_strchr(data, ','))
		(*(char *)ft_strchr(data, ',')) = ' ';
	s = ft_split(data, ' ');
	malloc_check(s);
	win->color.r = ft_atoi(s[1]);
	win->color.g = ft_atoi(s[2]);
	win->color.b = ft_atoi(s[3]);
	if (win->color.r > 255 || win->color.g > 255 || win->color.b > 255)
		close_error("Incorrect ARGB numbers\n");
	if (*data == 'F')
		win->color.f_color = win->color.a << 24 | win->color.r << 16 |
				win->color.g << 8 | win->color.b;
	else if (*data == 'C')
		win->color.c_color = win->color.a << 24 | win->color.r << 16 |
				win->color.g << 8 | win->color.b;
	delete_data(s);
}

/*
** Parse the 2D array and save the textures separately in the
** global window struct
**
** @param  char  *data passed string from 2D array
** @param  t_win  *win allocated global window structure
** @param  int       i reference to index position for textures
** @return void
*/

void	parse_tex(char *data, t_win *win, int i)
{
	char	*path;

	data += 2;
	while (*data && (*data == ' '))
		data++;
	path = ft_strdup(data);
	malloc_check(path);
	win->tex[i].wall = mlx_png_file_to_image(win->mlx, path,
			&win->tex[i].tex_w, &win->tex[i].tex_h);
	if (!win->tex[i].wall)
		close_error("Invalid texture\n");
	win->tex[i].data = mlx_get_data_addr(win->tex[i].wall,
			&win->tex[i].bpp, &win->tex[i].line_len, &win->tex[i].endian);
	if (!win->tex[i].data)
		close_error("Couldn't get texture data\n");
	free(path);
	win->color.c_color = (i == CEILING) ? 0xAA000000 : win->color.c_color;
	win->color.f_color = (i == FLOOR) ? 0xAA000000 : win->color.f_color;
}
