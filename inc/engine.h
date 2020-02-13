/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:29:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 12:01:51 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

/*
** ---------------------------------------------------------------------------
** 							Header includes
** ---------------------------------------------------------------------------
*/

# include <cub3d.h>

/*
** ---------------------------------------------------------------------------
** 							Engine functions
** ---------------------------------------------------------------------------
*/

int		render_next_frame(t_win *win);

void	move_right(t_mov *mov, t_win *win);
void	move_left(t_mov *mov, t_win *win);
void	move_up(t_mov *mov, t_win *win);
void	move_down(t_mov *mov, t_win *win);
void	rotate_l(t_mov *mov, t_win *win, double dir_x, double plane_x);
void	rotate_r(t_mov *mov, t_win *win, double dir_x, double plane_x);

void	draw_back(t_win *win);
void	draw_wall(t_win *win, int i, int y);
int		draw_tex(t_win *win, t_tex *tex, int i, int y);
void	draw_sprite(t_win *win, t_sdt *sdt, int i);
void	sprite_hide(t_win *win, double y, double x);

void	sprite_sort(t_spr *spr, int first, int last);
void	sprite_dist(t_win *win);

int		query_map(t_win *win, double y, double x);
int		px_color(t_tex *tex, double y, double x, int id);
void	pixel_put(t_img *img, int x, int y, int color);

#endif
