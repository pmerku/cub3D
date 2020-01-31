/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/31 15:20:03 by prmerku          ###   ########.fr       */
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

static int	px_color(t_tex *tex)
{
	return (*(int*)(tex->data
		+ (4 * tex->tex_w * (int)tex->tex_y) + (4 * (int)tex->tex_x)));
}

static int	draw_tex(t_win *win, t_tex *tex, int i, int y)
{
	u_int	color;

	win->ray.wall_x = (!win->mov.side)
			? win->pos.y + win->mov.perp_wd * win->ray.dir_y
			: win->pos.x + win->mov.perp_wd * win->ray.dir_x;
	win->ray.wall_x -= floor(win->ray.wall_x);
	tex->tex_x = (int)(win->ray.wall_x * tex->tex_w) % tex->tex_w;
	if (!win->mov.side && win->ray.dir_x > 0)
		tex->tex_x = tex->tex_w - tex->tex_x - 1;
	else if (win->mov.side && win->ray.dir_y < 0)
		tex->tex_x = tex->tex_w - tex->tex_x - 1;
	y = win->ray.draw_s;
	while (y < win->ray.draw_e)
	{
		tex->tex_y = (int)(((y - win->y * .5 + win->img[win->i].line_h * .5)
				* tex->tex_h) / win->img[win->i].line_h) % tex->tex_h;
		color = px_color(tex);
		pixel_put(&win->img[win->i], i, y, color);
		y++;
	}
	return (y);
}

static void	draw_pixels(t_win *win, int i)
{
	int		y;

	y = 0;
	if (win->mov.side)
		win->color.tex_i = (win->map.y < win->pos.y) ? W_WALL : E_WALL;
	else
		win->color.tex_i = (win->map.x < win->pos.x) ? N_WALL : S_WALL;
	while (y < win->ray.draw_s)
	{
		pixel_put(&win->img[win->i], i, y, win->color.c_color);
		y++;
	}
	y = draw_tex(win, &win->tex[win->color.tex_i], i, y);
	while (y < win->y)
	{
		pixel_put(&win->img[win->i], i, y, win->color.f_color);
		y++;
	}
}

int			query_map(t_win *win, double y, double x)
{
	if (y < 0 || y >= win->map.map_w || x < 0 || x >= win->map.map_h
		|| win->map.map[(int)y][(int)x] == '1')
	{
		if (win->map.map[(int)floor(y)][(int)floor(x)] == '1'
			|| win->map.map[(int)ceil(y)][(int)ceil(x)] == '1')
			win->mov.hit = 1;
		win->mov.hit = 1;
	}
	else
	{
		win->mov.hit = 0;
		return (0);
	}
	return (1);
}

int			render_next_frame(t_win *win)
{
	t_ray	*ray;
	t_mov	*mov;
	int		i;

	i = 0;
	ray = &win->ray;
	mov = &win->mov;
	move_pos(mov, win);
	while (i < win->x)
	{
		mov->hit = 0;
		init_ray(win, i);
		while (!mov->hit)
		{
			mov->side = (ray->side_dx >= ray->side_dy);
			ray->side_dx += (!mov->side) ? ray->delta_dx : 0;
			win->map.x += (!mov->side) ? mov->step_x : 0;
			ray->side_dy += (mov->side) ? ray->delta_dy : 0;
			win->map.y += (mov->side) ? mov->step_y : 0;
			query_map(win, win->map.y, win->map.x);
		}
		init_calc(win);
		draw_pixels(win, i);
		i++;
	}
	win->i = !win->i;
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img[win->i].img, 0, 0);
	return (0);
}
