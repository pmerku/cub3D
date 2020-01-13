/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/13 17:23:30 by prmerku          ###   ########.fr       */
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

static int 	map_check(t_win *win)
{
	if ((win->map.x < 0 && win->map.x > win->map.map_l) ||
		(win->map.y < 0 && win->map.y > win->map.map_h))
		close_error(2);
	if (win->map.map[win->map.x][win->map.map_l] > 0)
		return (1);
	return (0);
}

static void	init_pos(t_win *win)
{
	win->pos.x = 20;
	win->pos.y = 12;
	win->pos.dir_x = -1;
	win->pos.dir_y = 0;
	win->pos.plane_x = 0;
	win->pos.plane_y = 0.66;
}

int			render_next_frame(t_win *win)
{
	int		i;

	i = 0;
	init_pos(win);
	while (i < win->x)
	{
		win->pos.camera_x = 2 * i / (double)win->x - 1;
		win->ray.dir_x = win->pos.dir_x + win->pos.plane_x * win->pos.camera_x;
		win->ray.dir_y = win->pos.dir_y + win->pos.plane_y * win->pos.camera_x;
		win->map.x = (int)win->pos.x;
		win->map.y = (int)win->pos.y;
		win->map.map_l = win->pos.y;
		win->ray.delta_dx = fabs(1 / win->ray.dir_x);
		win->ray.delta_dy = fabs(1 / win->ray.dir_y);
		win->mov.step_x = (win->ray.dir_x < 0) ? -1 : 1;
		win->mov.step_y = (win->ray.dir_y < 0) ? -1 : 1;
		win->ray.side_dx = (win->ray.dir_x < 0) ?
				(win->pos.x - win->map.x) * win->ray.delta_dx :
				(win->map.x + 1.0 - win->pos.x) * win->ray.delta_dx;
		win->ray.side_dy = (win->ray.dir_y < 0) ?
						   (win->pos.y - win->map.map_l) * win->ray.delta_dy :
						   (win->map.map_l + 1.0 - win->pos.y) * win->ray.delta_dy;
		while (win->mov.hit == 0)
		{
			win->ray.side_dx = (win->ray.side_dx < win->ray.side_dy) ?
					win->ray.side_dx + win->ray.delta_dx :
					win->ray.side_dy + win->ray.delta_dy;
			win->map.x = (win->ray.side_dx < win->ray.side_dy) ?
					win->map.x + win->mov.step_x : win->map.map_l + win->mov.step_y;
			win->mov.hit = map_check(win);
		}
		i++;
		win->mov.perp_wd = (win->mov.side == 0) ? // <-- norme this
				(win->map.x - win->pos.x + (1 - win->mov.step_x) / 2) / win->ray.dir_x :
						   (win->map.map_l - win->pos.y + (1 - win->mov.step_y) / 2) / win->ray.dir_y;
		win->img.line_h = (int)(win->y / win->mov.perp_wd);
		int drawStart = -win->img.line_h / 2 + win->y / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = win->img.line_h / 2 + win->y / 2;
		if (drawEnd >= win->y)
			drawEnd = win->y - 1;
		pixel_put(&win->img, drawEnd, drawStart, win->tex.f_color);
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	return (0);
}
