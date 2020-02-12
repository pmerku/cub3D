/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:46:30 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/12 13:44:50 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <engine.h>

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

void	draw_wall(t_win *win, int i, int y)
{
	if (win->mov.side)
		win->color.tex_i = (win->map.y < win->pos.y) ? W_WALL : E_WALL;
	else
		win->color.tex_i = (win->map.x < win->pos.x) ? N_WALL : S_WALL;
	if (win->map.map[win->map.y][win->map.x] == 'H')
		win->color.tex_i = SPR_TR;		// TODO: in case no tex provided (segfault)
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
