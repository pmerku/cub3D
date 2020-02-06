/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:44:25 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/06 08:36:52 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <engine.h>
#include <cub3d.h>

static void	move_up_down(t_mov *mov, t_win *win)
{
	double	dir;
	double	dir2;

	dir = win->pos.dir_y * mov->m_speed;
	dir2 = win->pos.dir_x * mov->m_speed;
	if (win->key.up && query_map(win, win->pos.y, win->pos.x + dir) == 0)
		win->pos.x += dir;
	if (win->key.up && query_map(win, win->pos.y + dir2, win->pos.x) == 0)
		win->pos.y += dir2;
	if (win->key.down && query_map(win, win->pos.y, win->pos.x - dir) == 0)
		win->pos.x -= dir;
	if (win->key.down && query_map(win, win->pos.y - dir2, win->pos.x) == 0)
		win->pos.y -= dir2;
}

static void	move_left_right(t_mov *mov, t_win *win)
{
	double	dir;
	double	dir2;

	dir = cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed;
	dir2 = cos(acos(win->pos.dir_y) + M_PI) * mov->m_speed;
	if (win->key.left && query_map(win, win->pos.y, win->pos.x - dir) == 0)
		win->pos.x -= dir;
	if (win->key.left && query_map(win, win->pos.y + dir2, win->pos.x) == 0)
		win->pos.y += dir2;
	if (win->key.right && query_map(win, win->pos.y, win->pos.x + dir) == 0)
		win->pos.x += dir;
	if (win->key.right && query_map(win, win->pos.y - dir2, win->pos.x) == 0)
		win->pos.y -= dir2;
}

static void	rotate(t_mov *mov, t_win *win, double dir_x, double plane_x)
{
	double	rot;

	if (win->key.rot_l)
	{
		rot = mov->r_speed;
		win->pos.dir_x = win->pos.dir_x * cos(rot) - win->pos.dir_y * sin(rot);
		win->pos.dir_y = dir_x * sin(rot) + win->pos.dir_y * cos(rot);
		win->pos.plane_x =
				win->pos.plane_x * cos(rot) - win->pos.plane_y * sin(rot);
		win->pos.plane_y = plane_x * sin(rot) + win->pos.plane_y * cos(rot);
	}
	if (win->key.rot_r)
	{
		rot = -mov->r_speed;
		win->pos.dir_x = win->pos.dir_x * cos(rot) - win->pos.dir_y * sin(rot);
		win->pos.dir_y = dir_x * sin(rot) + win->pos.dir_y * cos(rot);
		win->pos.plane_x =
				win->pos.plane_x * cos(rot) - win->pos.plane_y * sin(rot);
		win->pos.plane_y = plane_x * sin(rot) + win->pos.plane_y * cos(rot);
	}
}

void		move_pos(t_mov *mov, t_win *win)
{
	double	dir_x;
	double	plane_x;
	double	time_old1;

	time_old1 = win->time_old0;
	win->time_delta = ((double)clock() - time_old1) / 1000;
	win->time_old0 = (double)clock();
	win->mov.m_speed = win->time_delta / 16 * MOV_SPEED;
	win->mov.r_speed = win->time_delta / 16 * ROT_SPEED;
	if ((win->key.right || win->key.left) && (win->key.up || win->key.down))
		mov->m_speed /= 2;
	dir_x = win->pos.dir_x;
	plane_x = win->pos.plane_x;
	move_up_down(mov, win);
	move_left_right(mov, win);
	rotate(mov, win, dir_x, plane_x);
}
