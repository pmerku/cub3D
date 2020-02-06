/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 07:46:30 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/06 07:47:51 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <engine.h>

int		draw_tex(t_win *win, t_tex *tex, int i, int y)
{
	u_int	color;

	win->ray.wall_x = (!win->mov.side)
			? win->pos.y + win->mov.perp_wd * win->ray.dir_y
			: win->pos.x + win->mov.perp_wd * win->ray.dir_x;
	win->ray.wall_x -= floor(win->ray.wall_x);
	tex->tex_x = (int)(win->ray.wall_x * tex->tex_w) % tex->tex_w;
	y = win->ray.draw_s;
	while (y < win->ray.draw_e)
	{
		tex->tex_y = (int)(((y - win->y * .5 + win->img[win->i].line_h * .5)
				* tex->tex_h) / win->img[win->i].line_h) % tex->tex_h;
		color = px_color(tex, tex->tex_y, tex->tex_x, win->color.tex_i);
		pixel_put(&win->img[win->i], i, y, color);
		y++;
	}
	return (y);
}

void	draw_wall(t_win *win, int i)
{
	int		y;

	y = 0;
	if (win->mov.side)
		win->color.tex_i = (win->map.y < win->pos.y) ? W_WALL : E_WALL;
	else
		win->color.tex_i = (win->map.x < win->pos.x) ? N_WALL : S_WALL;
	if (win->map.map[win->map.y][win->map.x] == '2')
		win->color.tex_i = E_WALL;
	while (y < win->ray.draw_s && y < win->y)
	{
		if (win->tex[CEILING].wall == NULL)
			pixel_put(&win->img[win->i], i, y, win->color.c_color);
		y++;
	}
	y = draw_tex(win, &win->tex[win->color.tex_i], i, y);
	while (y < win->y)
	{
		if (win->tex[FLOOR].wall == NULL)
			pixel_put(&win->img[win->i], i, y, win->color.f_color);
		y++;
	}
}
