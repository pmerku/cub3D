/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/06 07:56:02 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <time.h>
#include <engine.h>
#include <cub3d.h>

static void	init_ray(t_win *win, int i)
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

static void	init_calc(t_win *win)
{
	win->mov.perp_wd = (!win->mov.side)
			? (win->map.x - win->pos.x
			+ (1. - win->mov.step_x) / 2) / win->ray.dir_x
			: (win->map.y - win->pos.y
			+ (1. - win->mov.step_y) / 2) / win->ray.dir_y;
	win->img[win->i].line_h = (int)(win->y / win->mov.perp_wd);
	win->ray.draw_s = (win->img[win->i].line_h * -1) / 2 + win->y / 2;
	win->ray.draw_s = (win->ray.draw_s < 0) ? 0 : win->ray.draw_s;
	win->ray.draw_e = win->img[win->i].line_h / 2 + win->y / 2;
	win->ray.draw_e = (win->ray.draw_e >= win->y)
			? win->y - 1 : win->ray.draw_e;
}

int			render_next_frame(t_win *win)
{
	int		i;
	double	time_old1;

	i = 0;
	time_old1 = win->time_old0;
	win->time_delta = ((double)clock() - time_old1) / 1000;
	win->time_old0 = (double)clock();
	win->mov.m_speed = win->time_delta / 16 * MOV_SPEED;
	win->mov.r_speed = win->time_delta / 16 * ROT_SPEED;

	move_pos(&win->mov, win);
	draw_back(win);
	while (i < win->x)
	{
		win->mov.hit = 0;
		init_ray(win, i);
		while (!win->mov.hit)
		{
			win->mov.side = (win->ray.side_dx >= win->ray.side_dy);
			win->ray.side_dx += (!win->mov.side) ? win->ray.delta_dx : 0;
			win->map.x += (!win->mov.side) ? win->mov.step_x : 0;
			win->ray.side_dy += (win->mov.side) ? win->ray.delta_dy : 0;
			win->map.y += (win->mov.side) ? win->mov.step_y : 0;
			query_map(win, win->map.y, win->map.x);
		}
		init_calc(win);
		draw_wall(win, i);
		//win->spr.zbuff[i] = win->mov.perp_wd;
		i++;
	}
	// TODO: sprite
	if (win->map.map[win->map.y][win->map.x] == '2')
	{
		win->spr.x = win->map.x;
		win->spr.y = win->map.y;
	}
	//draw_sprite(win, i);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img[win->i].img, 0, 0);
	win->i = !win->i;
	return (0);
}
