/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:52:18 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/06 08:32:59 by prmerku          ###   ########.fr       */
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
	color = px_color(tex, win->mov.ty, win->mov.tx, 1);
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
	win->mov.step_fx = win->pos.rwd * (win->ray.dir_x1 - win->ray.dir_x0)
			/ win->x;
	win->mov.step_fy = win->pos.rwd * (win->ray.dir_y1 - win->ray.dir_y0)
			/ win->x;
	win->ray.fx = win->pos.x + win->pos.rwd * win->ray.dir_x0;
	win->ray.fy = win->pos.y + win->pos.rwd * win->ray.dir_y0;
	x = 0;
	while (x < win->x)
	{
		if (y > win->y / 2)
			draw_px_back(win, x, y);
		x++;
	}
}

// TODO: fix floor/ceiling textures
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
