/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:25:22 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 12:20:12 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_l(t_mov *mov, t_win *win, double dir_x, double plane_x)
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

void	rotate_r(t_mov *mov, t_win *win, double dir_x, double plane_x)
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
