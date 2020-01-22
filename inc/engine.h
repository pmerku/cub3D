/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:29:49 by prmerku           #+#    #+#             */
/*   Updated: 2020/01/21 15:48:22 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <cub3d.h>

int		render_next_frame(t_win *win);

void	init_pos(t_win *win);
void	init_ray(t_win *win, int i);
void	init_calc(t_win *win);

int		map_check(t_win *win, int x, int y);
void	move_pos(t_win *win);

#endif
