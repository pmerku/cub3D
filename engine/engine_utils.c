/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prmerku <prmerku@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:18:46 by prmerku           #+#    #+#             */
/*   Updated: 2020/02/20 09:28:04 by prmerku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include "utils.h"
#include "cub3d.h"

/**
 * Put pixel color on image
 * @param img pointer to current image
 * @param x position x on image
 * @param y position y on image
 * @param color pixel color value
 */
void		pixel_put(t_img *img, int x, int y, int color) {
	*(unsigned int*)(img->addr + (y * img->line_len + x * (img->bpp / 8))) = color;
}

/**
 * Get pixel color value from texture
 * @param tex pointer to current texture
 * @param y position y in texture
 * @param x position x in texture
 * @param id texture id
 * @return color value
 */
int			px_color(t_tex *tex, double y, double x, int id) {
	if (x >= 0 && x < tex->tex_w && y >= 0 && y < tex->tex_h) {
		if (id == N_WALL || id == E_WALL)
			return (*(int*)(tex->data + (tex->line_len * (int)y) + (4 * tex->tex_w) - (((int)x + 1) * 4)));
		else
			return (*(int*)(tex->data + (tex->line_len * (int)y) + (4 * (int)x)));
	}
	return 0x0;
}

/**
 * Hide sprite if it's an item and player walked over it
 * @param win global game structure
 * @param y player y position
 * @param x player x position
 */
void		sprite_hide(t_win *win, double y, double x) {
	if (!ft_strchr(HIT_P, win->map.map[(int)y][(int)x]))
		return ;
	if (win->map.map[(int)y][(int)x] == 'T')
		win->health -= 1. / 3;
	else {
		if (win->map.map[(int)y][(int)x] == 'P')
			win->score += 1. / win->spr_p;
		else {
			if (win->health != 1)
				win->health += 1. / 3;
		}
	}
	for (int i = 0; i < win->spr_i; i++) {
		if ((int)win->spr[i].x == (int)x && (int)win->spr[i].y == (int)y) {
			win->map.map[(int)y][(int)x] = '0';
			win->spr[i].hide = 1;
			return;
		}
	}
}

/**
 * Open / close door
 * @param win global game structure
 * @param y player y position
 * @param x player x position
 * @return status code
 */
int			open_door(t_win *win, double y, double x) {
	if (win->key.open)
		// add player offset
		if (win->map.map[(int)y][(int)x] == 'D') {
			win->mov.hit = !win->mov.hit;
			return 1;
		}
	return 0;
}
