/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:46:30 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/19 10:17:49 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>
#include <stddef.h>
#include <engine.h>

/*
** Calling function for wall texture drawing
**
** @param  t_win *win allocated global window structure
** @param  t_tex *tex allocated texture structure
** @param  int      i ray-caster index
** @param  int      y position y on screen
** @return void
*/

int		draw_tex(t_win *win, t_tex *tex, int i, int y)
{
	win->ray.wall_x = (!win->mov.side)
			? win->pos.y + win->mov.perp_wd * win->ray.dir_y
			: win->pos.x + win->mov.perp_wd * win->ray.dir_x;
	win->ray.wall_x -= floor(win->ray.wall_x);
	tex->tex_x = (int)(win->ray.wall_x * tex->tex_w) % tex->tex_w;
	y = win->ray.draw_s;
	while (y <= win->ray.draw_e && y < win->y)
	{
		tex->tex_y = (int)(((y - win->y * .5 + win->img[win->i].line_h * .5)
				* tex->tex_h) / win->img[win->i].line_h) % tex->tex_h;
		pixel_put(&win->img[win->i], i, y,
				px_color(tex, tex->tex_y, tex->tex_x, win->color.tex_i));
		y++;
	}
	return (y);
}

/*
** Calling function for wall texture selection and floor and ceiling protection
** in case no floor/ceiling texture is provided
**
** @param  t_win *win allocated global window structure
** @param  int      i ray-caster index
** @param  int      y position y on screen
** @return void
*/

void	draw_wall(t_win *win, int i, int y)
{
	if (win->mov.side)
		win->color.tex_i = (win->map.y < win->pos.y) ? W_WALL : E_WALL;
	else
		win->color.tex_i = (win->map.x < win->pos.x) ? N_WALL : S_WALL;
	if (win->map.map[win->map.y][win->map.x] == 'H')
		win->color.tex_i = DOOR_H;
	else if (win->map.map[win->map.y][win->map.x] == 'D')
		win->color.tex_i = DOOR;
	if (win->tex[CEILING].wall == NULL)
	{
		while (y < win->ray.draw_s && y < win->y)
		{
			pixel_put(&win->img[win->i], i, y, win->color.c_color);
			y++;
		}
	}
	y = draw_tex(win, &win->tex[win->color.tex_i], i, win->ray.draw_s);
	if (win->tex[FLOOR].wall == NULL)
	{
		while (y < win->y)
		{
			pixel_put(&win->img[win->i], i, y, win->color.f_color);
			y++;
		}
	}
}
