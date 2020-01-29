/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/29 13:40:56 by prmerku          ###   ########.fr       */
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
	while (y < win->ray.draw_s)
	{
		pixel_put(&win->img[win->i], i, y, win->color.c_color);
		y++;
	}
	while (y <= win->ray.draw_e)
	{
//		win->color.tex_y = (int)win->color.tex_pos & (win->tex[win->color.tex_i].tex_h - 1);
//		win->color.tex_pos += win->color.step;
//		win->color.tex_c = win->tex[win->color.tex_i].data[win->tex[win->color.tex_i].tex_h * win->color.tex_y + win->color.tex_x];
//		if (win->mov.side == 1)
//			win->color.tex_c = (win->color.tex_c >> 1) & 8355711;
//		pixel_put(&win->img, i, y, (win->mov.side == 1)
//		? win->color.tex_c : (win->color.tex_c >> 1) & 8355711);
		pixel_put(&win->img[win->i], i, y, (win->mov.side == 1) ? 0x00FF0000 : 0x00AA0000);
		y++;
	}
	while (y < win->y)
	{
		pixel_put(&win->img[win->i], i, y, win->color.f_color);
		y++;
	}
}

int			query_map(t_win *win, int x, int y)
{
	if (y <= 0 || y >= win->map.map_w || x <= 0 || x >= win->map.map_h
		|| win->map.map[x][y] == '1')
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
			query_map(win, win->map.y, win->map.x);
		}
		init_calc(win);

		// TODO: norm
		// TODO: texture printing
		if (win->mov.side)
			win->color.tex_i = (win->map.y < win->pos.y) ? W_WALL : E_WALL;
		else
			win->color.tex_i = (win->map.x < win->pos.x) ? N_WALL : S_WALL;

		double wallX;
		wallX = (!win->mov.side)
				? win->pos.y + win->mov.perp_wd * win->ray.dir_y
				: win->pos.x + win->mov.perp_wd * win->ray.dir_x;
		wallX -= floor(wallX);

		win->color.tex_x = (int)(wallX * (double)win->tex[win->color.tex_i].tex_w);
		if ((win->mov.side == 0 && win->ray.dir_x > 0) || (win->mov.side == 1 && win->ray.dir_y < 0))
			win->color.tex_x = win->tex[win->color.tex_i].tex_w - win->color.tex_x - 1;
		win->color.step = 1.0 * win->tex[win->color.tex_i].tex_h / win->img[win->i].line_h;
		win->color.tex_pos = (win->ray.draw_s - win->y / 2 + win->img[win->i].line_h / 2) * win->color.step;

		draw_pixels(win, i);
		i++;
	}
	win->i = !win->i;
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img[win->i].img, 0, 0);
	return (0);
}
