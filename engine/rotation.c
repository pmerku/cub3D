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

#include <math.h>
#include "cub3d.h"

/**
 * Rotate view left
 * @param mov movement structure
 * @param win global game structure
 * @param dir reference direction
 * @param plane reference plane
 */
void	rotate_l(t_mov *mov, t_win *win, double dir, double plane) {
	win->pos.dir_x = win->pos.dir_x * cos(mov->r_speed) - win->pos.dir_y * sin(mov->r_speed);
	win->pos.dir_y = dir * sin(mov->r_speed) + win->pos.dir_y * cos(mov->r_speed);
	win->pos.plane_x = win->pos.plane_x * cos(mov->r_speed) - win->pos.plane_y * sin(mov->r_speed);
	win->pos.plane_y = plane * sin(mov->r_speed) + win->pos.plane_y * cos(mov->r_speed);
}

/**
 * Rotate view right
 * @param mov movement structure
 * @param win global game structure
 * @param dir reference direction
 * @param plane reference plane
 */
void	rotate_r(t_mov *mov, t_win *win, double dir, double plane) {
	win->pos.dir_x = win->pos.dir_x * cos(-mov->r_speed) - win->pos.dir_y * sin(-mov->r_speed);
	win->pos.dir_y = dir * sin(-mov->r_speed) + win->pos.dir_y * cos(-mov->r_speed);
	win->pos.plane_x = win->pos.plane_x * cos(-mov->r_speed) - win->pos.plane_y * sin(-mov->r_speed);
	win->pos.plane_y = plane * sin(-mov->r_speed) + win->pos.plane_y * cos(-mov->r_speed);
}
