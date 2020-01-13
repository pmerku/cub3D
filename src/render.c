/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/13 15:02:04 by prmerku          ###   ########.fr       */
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

static void	init_pos(t_win *win)
{
	win->pos.x = 22;
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
		win->map.x = win->pos.x;
		win->map.y = win->pos.y;
		win->ray.delta_dx = fabs(1 / win->ray.dir_x);
		win->ray.delta_dy = fabs(1 / win->ray.dir_y);
		win->mov.step_x = (win->ray.dir_x < 0) ? -1 : 1;
		win->mov.step_y = (win->ray.dir_y < 0) ? -1 : 1;
		win->ray.side_dx = (win->ray.dir_x < 0) ?
				(win->pos.x - win->map.x) * win->ray.delta_dx :
				(win->map.x + 1.0 - win->pos.x) * win->ray.delta_dx;
		win->ray.side_dy = (win->ray.dir_y < 0) ?
				(win->pos.y - win->map.y) * win->ray.delta_dy :
				(win->map.y + 1.0 - win->pos.y) * win->ray.delta_dy;
		while (win->mov.hit == 0)
		{
			win->ray.side_dx = (win->ray.side_dx < win->ray.side_dy) ?
					win->ray.side_dx + win->ray.delta_dx :
					win->ray.side_dy + win->ray.delta_dy;
			win->map.x = (win->ray.side_dx < win->ray.side_dy) ?
					win->map.x + win->mov.step_x : win->map.y + win->mov.step_y;
			if (win->map.map[win->map.x][win->map.y] > 0) // <-- add map protection
				win->mov.hit = 1;
		}
		i++;
		win->mov.perp_wd = (win->mov.side == 0) ? // <-- norme this
				(win->map.x - win->pos.x + (1 - win->mov.step_x) / 2) / win->ray.dir_x :
				(win->map.y - win->pos.y + (1 - win->mov.step_y) / 2) / win->ray.dir_y;
		win->img.line_h = (int)(win->y / win->mov.perp_wd);
		int drawStart = -win->img.line_h / 2 + win->y / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = win->img.line_h / 2 + win->y / 2;
		if (drawEnd >= win->y)
			drawEnd = win->y - 1;
		pixel_put(&win->img, drawStart, drawEnd, 0x00FF0000);
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	return (0);
}
