/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:44:25 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 13:43:39 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>
#include <math.h>
#include <cub3d.h>

/*
** Move forward
**
** @param  t_mov  *mov allocated movement structure
** @param  t_win  *win allocated global window structure
** @return void
*/

void	move_up(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	+ win->pos.dir_y * mov->m_speed) == 0)
		win->pos.x += win->pos.dir_y * mov->m_speed;
	if (query_map(win, win->pos.y + win->pos.dir_x
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y += win->pos.dir_x * mov->m_speed;
	sprite_hide(win, win->pos.y, win->pos.x);
}

/*
** Move backwards
**
** @param  t_mov  *mov allocated movement structure
** @param  t_win  *win allocated global window structure
** @return void
*/

void	move_down(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	- win->pos.dir_y * mov->m_speed) == 0)
		win->pos.x -= win->pos.dir_y * mov->m_speed;
	if (query_map(win, win->pos.y - win->pos.dir_x
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y -= win->pos.dir_x * mov->m_speed;
	sprite_hide(win, win->pos.y, win->pos.x);
}

/*
** Strafe right
**
** @param  t_mov  *mov allocated movement structure
** @param  t_win  *win allocated global window structure
** @return void
*/

void	move_right(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	+ cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed) == 0)
		win->pos.x += cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed;
	if (query_map(win, win->pos.y - cos(acos(win->pos.dir_y) + M_PI)
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y -= cos(acos(win->pos.dir_y) + M_PI) * mov->m_speed;
	sprite_hide(win, win->pos.y, win->pos.x);
}

/*
** Strafe left
**
** @param  t_mov  *mov allocated movement structure
** @param  t_win  *win allocated global window structure
** @return void
*/

void	move_left(t_mov *mov, t_win *win)
{
	if (query_map(win, win->pos.y, win->pos.x
	- cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed) == 0)
		win->pos.x -= cos(acos(win->pos.dir_x) + M_PI) * mov->m_speed;
	if (query_map(win, win->pos.y + cos(acos(win->pos.dir_y) + M_PI)
	* mov->m_speed, win->pos.x) == 0)
		win->pos.y += cos(acos(win->pos.dir_y) + M_PI) * mov->m_speed;
	sprite_hide(win, win->pos.y, win->pos.x);
}
