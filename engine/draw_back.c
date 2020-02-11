/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:52:18 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/07 14:17:21 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <engine.h>

static void	draw_px(t_win *win, t_tex *tex, int x, int y)
{
	tex->tex_x = (int)(tex->tex_w * (win->ray.fx - win->mov.cell_x))
			& (tex->tex_w - 1);
	tex->tex_y = (int)(tex->tex_h * (win->ray.fy - win->mov.cell_y))
			& (tex->tex_h - 1);
	pixel_put(&win->img[win->i], x, y,
			px_color(tex, tex->tex_y, tex->tex_x, 1));
}

static void	draw_px_back(t_win *win, t_ray *ray, int x, int y)
{
	win->mov.cell_x = (int)ray->fx;
	win->mov.cell_y = (int)ray->fy;
	ray->fx += win->mov.step_fx;
	ray->fy += win->mov.step_fy;
	if (win->tex[CEILING].wall != NULL)
		draw_px(win, &win->tex[CEILING], x, win->y - y - 1);
	if (win->tex[FLOOR].wall != NULL)
		draw_px(win, &win->tex[FLOOR], x, y);
}

static void	draw_tex_back(t_win *win, t_ray *ray, int y)
{
	int		x;

	ray->dir_x0 = win->pos.dir_x - win->pos.plane_x;
	ray->dir_y0 = win->pos.dir_y - win->pos.plane_y;
	ray->dir_x1 = win->pos.dir_x + win->pos.plane_x;
	ray->dir_y1 = win->pos.dir_y + win->pos.plane_y;
	win->pos.rwd = (float)(.5 * win->y) / (float)(y - win->y / 2.);
	win->mov.step_fx = win->pos.rwd * (ray->dir_x1 - ray->dir_x0)
			/ (float)win->x;
	win->mov.step_fy = win->pos.rwd * (ray->dir_y1 - ray->dir_y0)
			/ (float)win->x;
	ray->fx = (float)win->pos.y + win->pos.rwd * ray->dir_x0;
	ray->fy = (float)win->pos.x + win->pos.rwd * ray->dir_y0;
	x = 0;
	while (x < win->x)
	{
		if (y > win->y / 2)
			draw_px_back(win, ray, x, y);
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
			draw_tex_back(win, &win->ray, y);
			y++;
		}
	}
}
