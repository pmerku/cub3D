/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:52:18 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/28 10:21:10 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_pos(t_win *win)
{
	win->pos.x = 2;
	win->pos.y = 8;
	win->pos.dir_x = 0;
	win->pos.dir_y = 1;
	win->pos.plane_x = 0.66;
	win->pos.plane_y = 0;
}

void	init_ray(t_win *win, int i)
{
	win->pos.camera_x = 2 * i / (double)win->x - 1;
	win->ray.dir_y = win->pos.dir_x + win->pos.plane_x * win->pos.camera_x;
	win->ray.dir_x = win->pos.dir_y + win->pos.plane_y * win->pos.camera_x;
	win->map.x = (int)win->pos.x;
	win->map.y = (int)win->pos.y;
	win->ray.delta_dx = fabs(1 / win->ray.dir_x);
	win->ray.delta_dy = fabs(1 / win->ray.dir_y);
	win->mov.step_x = (win->ray.dir_x < 0) ? -1 : 1;
	win->ray.side_dx = (win->ray.dir_x < 0)
			? (win->pos.x - win->map.x) * win->ray.delta_dx
			: (win->map.x + 1.0 - win->pos.x) * win->ray.delta_dx;
	win->mov.step_y = (win->ray.dir_y < 0) ? -1 : 1;
	win->ray.side_dy = (win->ray.dir_y < 0)
			? (win->pos.y - win->map.y) * win->ray.delta_dy
			: (win->map.y + 1.0 - win->pos.y) * win->ray.delta_dy;
}

void	init_calc(t_win *win)
{
	win->mov.perp_wd = (!win->mov.side)
			? (win->map.x - win->pos.x
			+ (1. - win->mov.step_x) / 2) / win->ray.dir_x
			: (win->map.y - win->pos.y
			+ (1. - win->mov.step_y) / 2) / win->ray.dir_y;
	win->img.line_h = (int)(win->y / win->mov.perp_wd);
	win->ray.draw_s = (win->img.line_h * -1) / 2 + win->y / 2;
	win->ray.draw_s = (win->ray.draw_s < 0) ? 0 : win->ray.draw_s;
	win->ray.draw_e = win->img.line_h / 2 + win->y / 2;
	win->ray.draw_e = (win->ray.draw_e >= win->y)
			? win->y - 1 : win->ray.draw_e;
}
