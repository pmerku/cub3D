/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/20 17:18:20 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <cub3d.h>

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static void 	map_check(t_win *win)
{
	if (win->map.x < 0 || win->map.x >= win->map.map_h ||
		win->map.y < 0 || win->map.y >= win->map.map_w)
		win->mov.hit = 1;
	else if (win->map.map[win->map.y][win->map.x] == '1') // <- x-y inverted ?
		win->mov.hit = 1;
	else
		win->mov.hit = 0;
}

void		init_pos(t_win *win)
{
	win->pos.x = 10;
	win->pos.y = 12;
	win->pos.dir_x = -1;
	win->pos.dir_y = 0;
	win->pos.plane_x = 0;
	win->pos.plane_y = 0.66;
	win->mov.m_speed = 0.5;
	win->mov.r_speed = 0.3;
}

void	move_pos(t_win *win)
{
	if (win->key.up)
	{
		if (win->map.map[(int)win->pos.y][(int)(win->pos.x + win->pos.dir_x * win->mov.m_speed)] == 0)
			win->pos.x += win->pos.dir_x * win->mov.m_speed;
		if (win->map.map[(int)(win->pos.y + win->pos.dir_y * win->mov.m_speed)][(int)win->pos.x] == 0)
			win->pos.y += win->pos.dir_y * win->mov.m_speed;
	}
	if (win->key.down)
	{
		if (win->map.map[(int)win->pos.y][(int)(win->pos.x - win->pos.dir_x * win->mov.m_speed)] == '0')
			win->pos.x -= win->pos.dir_x * win->mov.m_speed;
		if (win->map.map[(int)(win->pos.y - win->pos.dir_y * win->mov.m_speed)][(int)win->pos.x] == '0')
			win->pos.y -= win->pos.dir_y * win->mov.m_speed;
	}
	if (win->key.left)
	{
		double old_dirx = win->pos.dir_x;
		win->pos.dir_x = win->pos.dir_x * cos(-win->mov.r_speed) - win->pos.dir_y * sin(-win->mov.r_speed);
		win->pos.dir_y = old_dirx * sin(-win->mov.r_speed) + win->pos.dir_y * cos(-win->mov.r_speed);
		double old_planex = win->pos.plane_x;
		win->pos.plane_x = win->pos.plane_x * cos(-win->mov.r_speed) - win->pos.plane_y * sin(-win->mov.r_speed);
		win->pos.plane_y = old_planex * sin(-win->mov.r_speed) + win->pos.dir_y * cos(-win->mov.r_speed);
	}
	if (win->key.right)
	{
		double old_dirx = win->pos.dir_x;
		win->pos.dir_x = win->pos.dir_x * cos(win->mov.r_speed) - win->pos.dir_y * sin(win->mov.r_speed);
		win->pos.dir_y = old_dirx * sin(win->mov.r_speed) + win->pos.dir_y * cos(win->mov.r_speed);
		double old_planex = win->pos.plane_x;
		win->pos.plane_x = win->pos.plane_x * cos(win->mov.r_speed) - win->pos.plane_y * sin(win->mov.r_speed);
		win->pos.plane_y = old_planex * sin(win->mov.r_speed) + win->pos.dir_y * cos(win->mov.r_speed);
	}
}

int			render_next_frame(t_win *win)
{
	int		i;
	int drawStart;
	int drawEnd;

	i = 0;
	while (i < win->x)
	{
		win->mov.hit = 0;
		win->pos.camera_x = 2 * i / (double)win->x - 1;
		win->ray.dir_x = win->pos.dir_x + win->pos.plane_x * win->pos.camera_x;
		win->ray.dir_y = win->pos.dir_y + win->pos.plane_y * win->pos.camera_x;
		win->map.x = (int)win->pos.x;
		win->map.y = (int)win->pos.y;
		win->ray.delta_dx = fabs(1 / win->ray.dir_x);
		win->ray.delta_dy = fabs(1 / win->ray.dir_y);
		win->mov.step_x = (win->ray.dir_x < 0) ? -1 : 1;
		win->ray.side_dx = (win->ray.dir_x < 0) ?
				(win->pos.x - win->map.x) * win->ray.delta_dx :
				(win->map.x + 1.0 - win->pos.x) * win->ray.delta_dx;
		win->mov.step_y = (win->ray.dir_y < 0) ? -1 : 1;
		win->ray.side_dy = (win->ray.dir_y < 0) ?
				(win->pos.y - win->map.y) * win->ray.delta_dy :
				(win->map.y + 1.0 - win->pos.y) * win->ray.delta_dy;
		while (win->mov.hit == 0)
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
			map_check(win);
		}
		win->mov.perp_wd = (win->mov.side == 0) ?
		(win->map.x - win->pos.x + (1. - win->mov.step_x) / 2) / win->ray.dir_x :
		(win->map.y - win->pos.y + (1. - win->mov.step_y) / 2) / win->ray.dir_y;
		win->img.line_h = (int)(win->y / win->mov.perp_wd);
		drawStart = -(win->img.line_h) / 2 + win->y / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = win->img.line_h / 2 + win->y / 2;
		if (drawEnd >= win->y)
			drawEnd = win->y - 1;
		for (int y = drawStart; y < drawEnd; y++)
		{
			pixel_put(&win->img, i, y, 0x000000FF);
		}
		i++;
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	return (0);
}
