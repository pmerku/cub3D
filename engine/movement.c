/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:44:25 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/11 11:12:37 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <cub3d.h>

static void	move_up(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	+ win->pos.dir_y * mov->m_speed) == 0)
		win->pos.x += win->pos.dir_y * mov->m_speed;
	if (query_map(win, win->pos.y + win->pos.dir_x
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y += win->pos.dir_x * mov->m_speed;
}

static void	move_down(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	- win->pos.dir_y * mov->m_speed) == 0)
		win->pos.x -= win->pos.dir_y * mov->m_speed;
	if (query_map(win, win->pos.y - win->pos.dir_x
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y -= win->pos.dir_x * mov->m_speed;
}

static void	move_right(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y,win->pos.x
	+ cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed) == 0)
		win->pos.x += cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed;
	if (query_map(win, win->pos.y - cos(acos(win->pos.dir_y) + M_PI)
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y -= cos(acos(win->pos.dir_y) + M_PI) * mov->m_speed;
}

static void	move_left(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	- cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed) == 0)
		win->pos.x -= cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed;
	if (query_map(win, win->pos.y + cos(acos(win->pos.dir_y) + M_PI)
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y += cos(acos(win->pos.dir_y) + M_PI) * mov->m_speed;
}

static void	rotate_l(t_mov *mov, t_win *win, double dir_x, double plane_x)
{
	win->pos.dir_x = win->pos.dir_x * cos(mov->r_speed)
			- win->pos.dir_y * sin(mov->r_speed);
	win->pos.dir_y = dir_x * sin(mov->r_speed)
			+ win->pos.dir_y * cos(mov->r_speed);
	win->pos.plane_x = win->pos.plane_x * cos(mov->r_speed)
			- win->pos.plane_y * sin(mov->r_speed);
	win->pos.plane_y = plane_x * sin(mov->r_speed)
			+ win->pos.plane_y * cos(mov->r_speed);
}

static void	rotate_r(t_mov *mov, t_win *win, double dir_x, double plane_x)
{
	win->pos.dir_x = win->pos.dir_x * cos(-mov->r_speed)
			- win->pos.dir_y * sin(-mov->r_speed);
	win->pos.dir_y = dir_x * sin(-mov->r_speed)
			+ win->pos.dir_y * cos(-mov->r_speed);
	win->pos.plane_x = win->pos.plane_x * cos(-mov->r_speed)
			- win->pos.plane_y * sin(-mov->r_speed);
	win->pos.plane_y = plane_x * sin(-mov->r_speed)
			+ win->pos.plane_y * cos(-mov->r_speed);
}

// TODO: make this smooth
void		move_pos(t_mov *mov, t_win *win)
{
	win->mov.m_speed = MOV_SPEED;
	if ((win->key.up || win->key.down) && (win->key.right || win->key.left))
		win->mov.m_speed /= 1.8;
	if (win->key.up)
		move_up(mov, win);
	if (win->key.down)
		move_down(mov, win);
	if (win->key.left)
		move_left(mov, win);
	if (win->key.right)
		move_right(mov, win);
	if (win->key.rot_l)
		rotate_l(mov, win, win->pos.dir_x, win->pos.plane_x);
	if (win->key.rot_r)
		rotate_r(mov, win, win->pos.dir_x, win->pos.plane_x);
}
