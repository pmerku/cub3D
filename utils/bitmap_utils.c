/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 14:43:23 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/12 14:58:50 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

/*
** Get ARGB color form image x/y position
**
** @param  t_img *img allocated image structure
** @param  int      x position x in image
** @param  int      y position y in image
** @return u_int      color value
*/

u_int	get_px(t_img *img, int x, int y)
{
	return (*(u_int*)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

/*
** Get red value from ARGB color
**
** @param  u_int color color value
** @return u_int       R value
*/

u_int	get_r(u_int color)
{
	return ((color & 0xFF0000) >> 16);
}

/*
** Get green value from ARGB color
**
** @param  u_int color color value
** @return u_int       G value
*/

u_int	get_g(u_int color)
{
	return ((color & 0xFF00) >> 8);
}

/*
** Get blue value from ARGB color
**
** @param  u_int color color value
** @return u_int       B value
*/

u_int	get_b(u_int color)
{
	return (color & 0xFF);
}
