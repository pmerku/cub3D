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

#include "cub3d.h"

/**
 * Get ARGB pixel color from image
 * @param img pointer to the image
 * @param x position x in image
 * @param y position y in image
 * @return ARGB value
 */
u_int	get_px(t_img *img, int x, int y) {
	return (*(u_int*)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

/**
 * Get red value form ARGB color
 * @param color ARGB value
 * @return R value
 */
u_int	get_r(u_int color) {
	return ((color & 0xFF0000) >> 16);
}

/**
 * Get green value form ARGB color
 * @param color ARGB value
 * @return G value
 */
u_int	get_g(u_int color) {
	return ((color & 0xFF00) >> 8);
}

/**
 * Get blue value form ARGB color
 * @param color ARGB value
 * @return B value
 */
u_int	get_b(u_int color) {
	return (color & 0xFF);
}
