/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:52:18 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/05 15:33:27 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <engine.h>

static void	draw_px(t_win *win, t_tex *tex, int x, int y)
{
	u_int	color;

	win->mov.tx = (int)(tex->tex_w * (win->ray.fx - win->mov.cell_x))
			& (tex->tex_w - 1);
	win->mov.ty = (int)(tex->tex_h * (win->ray.fy - win->mov.cell_y))
			& (tex->tex_h - 1);
	color = px_color(tex, 1);
	pixel_put(&win->img[win->i], x, y, color);
}

static void	draw_px_back(t_win *win, int x, int y)
{
	win->mov.cell_x = (int)win->ray.fx;
	win->mov.cell_y = (int)win->ray.fy;
	win->ray.fx += win->mov.step_fx;
	win->ray.fy += win->mov.step_fy;
	if (win->tex[CEILING].wall != NULL)
		draw_px(win, &win->tex[CEILING], x, win->y - y - 1);
	if (win->tex[FLOOR].wall != NULL)
		draw_px(win, &win->tex[FLOOR], x, y);
}

static void	draw_tex_back(t_win *win, int y)
{
	int		x;

	win->ray.dir_x0 = win->ray.dir_x - win->pos.plane_x;
	win->ray.dir_y0 = win->ray.dir_y - win->pos.plane_y;
	win->ray.dir_x1 = win->ray.dir_x + win->pos.plane_x;
	win->ray.dir_y1 = win->ray.dir_y + win->pos.plane_y;
	win->pos.rwd = (.5 * win->y) / (y - win->y / 2);
	win->mov.step_fx = win->pos.rwd
			* (win->ray.dir_x1 - win->ray.dir_x0) / win->x;
	win->mov.step_fy = win->pos.rwd
			* (win->ray.dir_y1 - win->ray.dir_y0) / win->x;
	win->ray.fx = win->pos.y + win->pos.rwd * win->ray.dir_x0;
	win->ray.fy = win->pos.x + win->pos.rwd * win->ray.dir_y0;
	x = 0;
	while (x < win->x)
	{
		if (y > win->y / 2)
			draw_px_back(win, x, y);
		x++;
	}
}

void		draw_back(t_win *win)
{
	int		y;

	y = 0;
	if (win->tex[FLOOR].wall != NULL || win->tex[CEILING].wall != NULL)
	{
		while (y < win->y)
		{
			draw_tex_back(win, y);
			y++;
		}
	}
}

int			draw_tex(t_win *win, t_tex *tex, int i, int y)
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
		color = px_color(tex, win->color.tex_i);
		pixel_put(&win->img[win->i], i, y, color);
		y++;
	}
	return (y);
}
