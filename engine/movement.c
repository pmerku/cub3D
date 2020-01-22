/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:44:25 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/22 09:24:12 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <cub3d.h>

static void	move_up_down(t_win *win)
{
	if (win->key.up && map_check(win, (int)win->pos.y,
			(int)(win->pos.x + win->pos.dir_x * win->mov.m_speed)) == 0)
		win->pos.x += win->pos.dir_x * win->mov.m_speed;
	if (win->key.up && map_check(win,(int)(win->pos.y
	+ win->pos.dir_y * win->mov.m_speed), (int)win->pos.x) == 0)
		win->pos.y += win->pos.dir_y * win->mov.m_speed;
	if (win->key.down && map_check(win, (int)win->pos.y,
			(int)(win->pos.x - win->pos.dir_x * win->mov.m_speed)) == 0)
		win->pos.x -= win->pos.dir_x * win->mov.m_speed;
	if (win->key.down && map_check(win, (int)(win->pos.y
	- win->pos.dir_y * win->mov.m_speed), (int)win->pos.x) == 0)
		win->pos.y -= win->pos.dir_y * win->mov.m_speed;
}

static void	move_left_right(t_win *win)
{
	double	dir;
	double	dir2;

	dir = cos(acos(win->pos.dir_y) + M_PI);
	dir2 = cos(acos(win->pos.dir_x) + M_PI);
	if (win->key.right && map_check(win, (int)win->pos.y,
			(int)(win->pos.x - dir * win->mov.m_speed)) == 0)
		win->pos.x -= dir * win->mov.m_speed;
	if (win->key.right && map_check(win,(int)(win->pos.y
	+ dir2 * win->mov.m_speed), (int)win->pos.x) == 0)
		win->pos.y += dir2 * win->mov.m_speed;
	if (win->key.left && map_check(win, (int)win->pos.y,
			(int)(win->pos.x + dir * win->mov.m_speed)) == 0)
		win->pos.x += dir * win->mov.m_speed;
	if (win->key.left && map_check(win,(int)(win->pos.y
	- dir2 * win->mov.m_speed), (int)win->pos.x) == 0)
		win->pos.y -= dir2 * win->mov.m_speed;
}

static void	rotate(t_win *win, double dir_x, double plane_x)
{
	if (win->key.rot_l)
	{
		win->pos.dir_x = win->pos.dir_x * cos(win->mov.r_speed)
				- win->pos.dir_y * sin(win->mov.r_speed);
		win->pos.dir_y = dir_x * sin(win->mov.r_speed)
				+ win->pos.dir_y * cos(win->mov.r_speed);
		win->pos.plane_x = win->pos.plane_x * cos(win->mov.r_speed)
				- win->pos.plane_y * sin(win->mov.r_speed);
		win->pos.plane_y = plane_x * sin(win->mov.r_speed)
				+ win->pos.plane_y * cos(win->mov.r_speed);
	}
	if (win->key.rot_r)
	{
		win->pos.dir_x = win->pos.dir_x * cos(-win->mov.r_speed)
				- win->pos.dir_y * sin(-win->mov.r_speed);
		win->pos.dir_y = dir_x * sin(-win->mov.r_speed)
				+ win->pos.dir_y * cos(-win->mov.r_speed);
		win->pos.plane_x = win->pos.plane_x * cos(-win->mov.r_speed)
				- win->pos.plane_y * sin(-win->mov.r_speed);
		win->pos.plane_y = plane_x * sin(-win->mov.r_speed)
				+ win->pos.plane_y * cos(-win->mov.r_speed);
	}
}

void		move_pos(t_win *win)
{
	double	dir_x;
	double	plane_x;

	dir_x = win->pos.dir_x;
	plane_x = win->pos.plane_x;
	move_up_down(win);
	move_left_right(win);
	rotate(win, dir_x, plane_x);
}
