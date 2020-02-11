/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/11 16:20:15 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <engine.h>
#include <cub3d.h>

static void	init_ray(t_win *win, t_ray *ray, int i)
{
	win->pos.camera_x = 2 * i / (double)win->x - 1;
	ray->dir_y = win->pos.dir_x + win->pos.plane_x * win->pos.camera_x;
	ray->dir_x = win->pos.dir_y + win->pos.plane_y * win->pos.camera_x;
	win->map.x = (int)win->pos.x;
	win->map.y = (int)win->pos.y;
	ray->delta_dx = fabs(1 / ray->dir_x);
	ray->delta_dy = fabs(1 / ray->dir_y);
	win->mov.step_x = (ray->dir_x < 0) ? -1 : 1;
	ray->side_dx = (ray->dir_x < 0)
		   	? (win->pos.x - win->map.x) * ray->delta_dx
		   	: (win->map.x + 1.0 - win->pos.x) * ray->delta_dx;
	win->mov.step_y = (ray->dir_y < 0) ? -1 : 1;
	ray->side_dy = (ray->dir_y < 0)
			? (win->pos.y - win->map.y) * ray->delta_dy
			: (win->map.y + 1.0 - win->pos.y) * ray->delta_dy;
}

static void	init_calc(t_win *win, t_ray *ray)
{
	win->mov.perp_wd = (!win->mov.side)
			? (win->map.x - win->pos.x
			+ (1. - win->mov.step_x) / 2) / ray->dir_x
			: (win->map.y - win->pos.y
			+ (1. - win->mov.step_y) / 2) / ray->dir_y;
	win->img[win->i].line_h = (int)(win->y / win->mov.perp_wd);
	ray->draw_s = (win->img[win->i].line_h * -1) / 2 + win->y / 2;
	ray->draw_s = (ray->draw_s < 0) ? 0 : ray->draw_s;
	ray->draw_e = win->img[win->i].line_h / 2 + win->y / 2;
	ray->draw_e = (ray->draw_e >= win->y)
			? win->y - 1 : ray->draw_e;
}

int			render_next_frame(t_win *win)
{
	int		i;

	i = 0;
	move_pos(&win->mov, win);
	draw_back(win);
	while (i < win->x)
	{
		win->mov.hit = 0;
		init_ray(win, &win->ray, i);
		while (!win->mov.hit)
		{
			if (win->ray.side_dx < win->ray.side_dy)
			{
				win->ray.side_dx += win->ray.delta_dx;
				win->map.x += win->mov.step_x;
				win->mov.side = 0;
			}
			else
			{
				win->ray.side_dy += win->ray.delta_dy;
				win->map.y += win->mov.step_y;
				win->mov.side = 1;
			}
			query_map(win, win->map.y, win->map.x);
		}
		init_calc(win, &win->ray);
		draw_wall(win, i);
		win->z_buff[i] = win->mov.perp_wd;
		i++;
	}
	draw_sprite(win);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img[win->i].img, 0, 0);
	win->i = !win->i;
	return (0);
}
