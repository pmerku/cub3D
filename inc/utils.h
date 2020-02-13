/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 11:31:35 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/13 14:40:45 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*
** ---------------------------------------------------------------------------
** 							Header includes
** ---------------------------------------------------------------------------
*/

# include <cub3d.h>

/*
** ---------------------------------------------------------------------------
** 							Utils functions
** ---------------------------------------------------------------------------
*/

void	save_frame(t_win *win);
u_int	get_px(t_img *img, int x, int y);
u_int	get_r(u_int color);
u_int	get_g(u_int color);
u_int	get_b(u_int color);

int		close_win(t_win *win);
int		close_key(int keycode, t_win *win);
int		close_error(char *s);
void	delete_data(char **data);

void	malloc_check(void *ptr);
void	*ft_malloc(size_t size);

#endif
