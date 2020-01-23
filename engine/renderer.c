/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/23 17:01:17 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <engine.h>
#include <cub3d.h>

static void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static void	draw_pixels(t_win *win, int i)
{
	int		y;

	y = 0;
	while (y <= win->ray.draw_s)
	{
		pixel_put(&win->img, i, y, win->tex.c_color);
		y++;
	}
	while (y <= win->ray.draw_e)
	{
		pixel_put(&win->img, i, y, (win->mov.side)
		? 0x000000AA : 0x000000FF);
		y++;
	}
	while (y < win->y)
	{
		pixel_put(&win->img, i, y, win->tex.f_color);
		y++;
	}
}

int			map_check(t_win *win, int y, int x)
{
	if (x < 0 || x >= win->map.map_w || y < 0 || y >= win->map.map_h)
		win->mov.hit = 1;
	else if (win->map.map[y][x] == '1')
		win->mov.hit = 1;
	else
	{
		win->mov.hit = 0;
		return (0);
	}
	return (1);
}

int			render_next_frame(t_win *win)
{
	int		i;

	i = 0;
	move_pos(win);
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
			map_check(win, win->map.y, win->map.x);
		}
		int texNum = win->map.map[win->map.y][win->map.x] - '1';

		double wallX;
		wallX = (!win->mov.side) ? win->pos.y + win->mov.perp_wd * win->ray.dir_y
				: win->pos.x + win->mov.perp_wd * win->ray.dir_x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texWidth);
		if ((win->mov.side == 0 && win->ray.dir_x > 0) || (win->mov.side == 1 && win->ray.dir_y < 0))
			texX = texWidth - texX - 1;
		double step = 1.0 * texHeigth / win->img.line_h;
		double texPos = (win->ray.draw_s - win->y / 2 + win->img.line_h / 2) * step;
		for (int y = win->ray.draw_s; y < win->ray.draw_e; y++)
		{
			int texY = (int)texPos & (texHeigth - 1);
			texPos += step;
			color = tex[texNum][texHeigth * texY + texX];
			if (win->mov.side == 1)
				color = (color >> 1) & 8355711;

		}
		init_calc(win);
		draw_pixels(win, i);
		i++;
	}
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img.img, 0, 0);
	return (0);
}
