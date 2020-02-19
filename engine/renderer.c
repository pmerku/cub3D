/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:06:53 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/19 08:22:45 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <libft.h>
#include <engine.h>
#include <utils.h>
#include <cub3d.h>

/*
** Check if a wall is hit
**
** @param  t_win  *win allocated global window structure
** @param  double    y position x of player
** @param  double    x position y of player
** @return int         status code
*/

int			query_map(t_win *win, double y, double x)
{
	if (y < 0 || y >= win->map.map_h || x < 0
		|| x >= ft_strlen(win->map.map[(int)y])
		|| ft_strchr(HIT_C, win->map.map[(int)y][(int)x]))
	{
		win->mov.hit = 1;
		if (ft_strchr(HIT_NC, win->map.map[(int)y][(int)x]))
			return (0);
		if (open_door(win, y, x))
			return (0);
	}
	else if (ft_strchr(HIT_NC, win->map.map[(int)y][(int)x]))
	{
		win->mov.hit = 0;
		return (0);
	}
	return (1);
}

/*
** Calculations for the ray-caster
**
** @param  t_win *win allocated global window structure
** @param  t_ray *ray allocated ray-caster structure
** @param  int      i ray-caster index
** @return void
*/

static void	init_ray(t_win *win, t_ray *ray, int i)
{
	win->mov.hit = 0;
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

/*
** Calculations for the perpendicular wall distance
**
** @param  t_win *win allocated global window structure
** @param  t_ray *ray allocated ray-caster structure
** @return void
*/

static void	init_calc(t_win *win, t_ray *ray)
{
	win->mov.perp_wd = (!win->mov.side)
			? (win->map.x - win->pos.x
			+ (1. - win->mov.step_x) / 2) / ray->dir_x
			: (win->map.y - win->pos.y
			+ (1. - win->mov.step_y) / 2) / ray->dir_y;
	win->img[win->i].line_h = (int)(win->y / win->mov.perp_wd);
	ray->draw_s = -win->img[win->i].line_h / 2 + win->y / 2;
	ray->draw_s = (ray->draw_s < 0) ? 0 : ray->draw_s;
	ray->draw_e = win->img[win->i].line_h / 2 + win->y / 2;
	ray->draw_e = (ray->draw_e >= win->y)
			? win->y - 1 : ray->draw_e;
}

/*
** DDA algorithm
**
** @param  t_win *win allocated global window structure
** @param  int      i ray-caster index
** @return void
*/

static void	perform_dda(t_win *win, int i)
{
	while (i < win->x)
	{
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
		draw_wall(win, i, 0);
		win->z_buff[i] = win->mov.perp_wd;
		i++;
	}
}

/*
** Calling function to render every frame
**
** @param  t_win *win allocated global window structure
** @return int        status code
*/

int			render_next_frame(t_win *win)
{
	win->mov.m_speed = (win->health < .3 || win->score >= 1.) ? 0 : MOV_SPEED;
	if ((win->key.up || win->key.down) && (win->key.right || win->key.left))
		win->mov.m_speed /= 1.8;
	if (win->key.up)
		move_up(&win->mov, win);
	if (win->key.down)
		move_down(&win->mov, win);
	if (win->key.left)
		move_left(&win->mov, win);
	if (win->key.right)
		move_right(&win->mov, win);
	if (win->key.rot_l)
		rotate_l(&win->mov, win, win->pos.dir_x, win->pos.plane_x);
	if (win->key.rot_r)
		rotate_r(&win->mov, win, win->pos.dir_x, win->pos.plane_x);
	draw_back(win);
	sprite_dist(win);
	perform_dda(win, 0);
	draw_sprite(win, &win->sdt, 0);
	draw_hud(win);
	mlx_put_image_to_window(win->mlx, win->mlx_win, win->img[win->i].img, 0, 0);
	if (win->save)
		save_frame(win);
	win->i = !win->i;
	return (0);
}
